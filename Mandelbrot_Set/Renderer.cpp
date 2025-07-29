#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>

using namespace std;

Renderer::Renderer(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

void Renderer::render(VAO& vao, Texture& mandelbrotTexture, Shader& displayShader,
    ComputeShader& computeShader, float& zoom, float& center_x, float& center_y)
{
    computeShader.Activate();
    computeShader.set_float("zoom", zoom);
    computeShader.set_float("center_x", center_x);
    computeShader.set_float("center_y", center_y);

    glDispatchCompute((screenWidth + 31) / 32, (screenHeight + 31) / 32, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    glClearColor(0.2f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    displayShader.Activate();
    vao.Bind();
    mandelbrotTexture.Activate();
    displayShader.set_int("mandelbrotTex", 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::clear(VAO& vao, VBO& vbo, EBO& ebo, Texture& mandelbrotTexture,
    Shader& displayShader, ComputeShader& computeShader)
{
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    mandelbrotTexture.Delete();
    displayShader.Delete();
    computeShader.Delete();
}