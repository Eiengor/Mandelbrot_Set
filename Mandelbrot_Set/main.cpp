#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <vector>
#include <chrono>
#include <numeric>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
#include "Texture.h"
#include "ComputeShader.h"
#include "Application.h"

using namespace std;
using namespace glm;

int screen_width = 1600;
int screen_height = 900;

int num_frames = 0;
float last_time = 0.0f;
float center_x = 0.0f;
float center_y = 0.0f;
float zoom = 1.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float vertices[] = {
    //    x      y      z   
        -1.0f, -1.0f, -0.0f,
         1.0f,  1.0f, -0.0f,
        -1.0f,  1.0f, -0.0f,
         1.0f, -1.0f, -0.0f
};

unsigned int indices[] = {
        0, 1, 2,
        0, 3, 1
};

void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        center_y = center_y + 0.01f * zoom;
        if (center_y > 1.0f)
        {
            center_y = 1.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        center_y = center_y - 0.01f * zoom;
        if (center_y < -1.0f)
        {
            center_y = -1.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        center_x = center_x - 0.01f * zoom;
        if (center_x < -1.0f)
        {
            center_x = -1.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        center_x = center_x + 0.01f * zoom;
        if (center_x > 1.0f)
        {
            center_x = 1.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        zoom = zoom * 1.04f;
        if (zoom > 1.0f)
        {
            zoom = 1.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        zoom = zoom * 0.96f;
        if (zoom < 0.00001f)
        {
            zoom = 0.00001f;
        }
    }
}

void countFPS() {
    double current_time = glfwGetTime();
    num_frames++;
    if (current_time - last_time >= 1.0) {
        cout << 1000.0 / num_frames << "ms / frame\n";
        num_frames = 0;
        last_time += 1.0;
    }
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();

    try
    {
        Application app(screen_width, screen_height, "Mandelbrot");
        Texture mandelbrotTexture(screen_width, screen_height);
        Shader displayShader("textureDisplay.vert", "textureDisplay.frag");
        ComputeShader computeShader("mandelbrotSet.comp");

        VAO vao;
        vao.Bind();
        VBO vbo(vertices, sizeof(vertices));
        EBO ebo(indices, sizeof(indices));
        vao.LinkVBO(vbo, 0);
        vao.Unbind();

        last_time = glfwGetTime();
        vector<float> fpsHistory;
        int fCounter = 0;
        int time_stopper = 0;

        while (!app.shouldClose())
        {
            app.beginFrame();

            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            process_input(app.getWindow());
            float fps = 1.0f / deltaTime;
            fpsHistory.push_back(fps);

            if (fCounter > 100) {
                cout << "FPS: " << fps << endl;
                fCounter = 0;
            }
            else {
                fCounter++;
            }

            computeShader.Activate();
            computeShader.set_float("zoom", zoom);
            computeShader.set_float("center_x", center_x);
            computeShader.set_float("center_y", center_y);

            glDispatchCompute((screen_width + 31) / 32, (screen_height + 31) / 32, 1);
            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

            glClearColor(0.2f, 0.0f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            displayShader.Activate();
            vao.Bind();
            mandelbrotTexture.Activate();
            displayShader.set_int("mandelbrotTex", 0);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            if (time_stopper == 0)
            {
                auto end_time = chrono::high_resolution_clock::now();
                chrono::duration<double> startup_duration = end_time - start_time;
                cout << "Startup time: " << startup_duration.count() << " seconds" << endl;
                time_stopper = 1;
            }

            app.endFrame();
        }
        if (!fpsHistory.empty()) {
            float sum = accumulate(fpsHistory.begin(), fpsHistory.end(), 0.0f);
            float avgFps = sum / fpsHistory.size();
            cout << "Average FPS: " << avgFps << endl;
        }

        vao.Delete();
        vbo.Delete();
        ebo.Delete();
        mandelbrotTexture.Delete();
        displayShader.Delete();
        computeShader.Delete();
        fpsHistory.clear();
        fpsHistory.shrink_to_fit();
        glfwTerminate();
        return 0;
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
}