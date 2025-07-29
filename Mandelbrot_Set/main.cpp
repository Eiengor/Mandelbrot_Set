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
#include "Renderer.h"
#include "InputHandler.h"

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
        Renderer renderer(screen_width, screen_height);
        InputHandler inputHandler;

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

            inputHandler.processInput(app.getWindow(), zoom, center_x, center_y);
            
            float fps = 1.0f / deltaTime;
            fpsHistory.push_back(fps);

            if (fCounter > 100) {
                cout << "FPS: " << fps << endl;
                fCounter = 0;
            }
            else {
                fCounter++;
            }

            renderer.render(vao, mandelbrotTexture, displayShader, computeShader,
                zoom, center_x, center_y);

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

        renderer.clear(vao, vbo, ebo, mandelbrotTexture, displayShader, computeShader);
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