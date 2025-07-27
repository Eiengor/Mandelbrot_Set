#include "Renderer.h"

float Renderer::vertices[12] = {
    -1.0f, -1.0f, -0.0f,
     1.0f,  1.0f, -0.0f,
    -1.0f,  1.0f, -0.0f,
     1.0f, -1.0f, -0.0f
};

unsigned int Renderer::indices[6] = {
    0, 1, 2,
    0, 3, 1
};

Renderer::Renderer(int width, int height, const char* vertexFile,
    const char* fragmentFile, const char* computeFile)
    : screenWidth(width), screenHeight(height),
    mandelbrotTexture(width, height),
    displayShader(vertexFile, fragmentFile),
    computeShader(computeFile),
    vbo(vertices, sizeof(vertices)),
    ebo(indices, sizeof(indices))
{
    vao.Bind();
    vao.LinkVBO(vbo, 0);
    vao.Unbind();
}

Renderer::~Renderer()
{
    clear();
}

void Renderer::render()
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

void Renderer::clear()
{
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    mandelbrotTexture.Delete();
    displayShader.Delete();
    computeShader.Delete();
}

void Renderer::setCenter(float x, float y)
{
    center_x = x;
    center_y = y;
}

void Renderer::setZoom(float newZoom)
{
    if (newZoom < 0.00001f) {
        zoom = 0.00001f;
    }
    else if (newZoom > 1.0f) {
        zoom = 1.0f;
    }
    else {
        zoom = newZoom;
    }
}

void Renderer::moveCenter(float deltaX, float deltaY)
{
    center_x += deltaX;
    center_y += deltaY;

    if (center_x < -1.0f) center_x = -1.0f;
    if (center_x > 1.0f) center_x = 1.0f;
    if (center_y < -1.0f) center_y = -1.0f;
    if (center_y > 1.0f) center_y = 1.0f;
}

void Renderer::adjustZoom(float factor)
{
    setZoom(zoom * factor);
}

void Renderer::onResize(int newWidth, int newHeight)
{
    screenWidth = newWidth;
    screenHeight = newHeight;
    mandelbrotTexture.Delete();
    mandelbrotTexture = Texture(screenWidth, screenHeight);
}
