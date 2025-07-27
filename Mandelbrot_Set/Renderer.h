#ifndef RENDERER_H
#define RENDERER_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
#include "ComputeShader.h"
#include "Texture.h"

class Renderer
{
private:
    VAO vao;
    VBO vbo;
    EBO ebo;
    Shader displayShader;
    ComputeShader computeShader;
    Texture mandelbrotTexture;

    float center_x = 0.0f;
    float center_y = 0.0f;
    float zoom = 1.0f;
    int screenWidth, screenHeight;
    static float vertices[12];
    static unsigned int indices[6];

public:
    Renderer(int width, int height, const char* vertexFile,
        const char* fragmentFile, const char* computeFile);
    ~Renderer();

    void render();
    void clear();

    void setCenter(float x, float y);
    void setZoom(float newZoom);
    void moveCenter(float deltaX, float deltaY);
    void adjustZoom(float factor);

    float getCenterX() const { return center_x; }
    float getCenterY() const { return center_y; }
    float getZoom() const { return zoom; }

    void onResize(int newWidth, int newHeight);

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
};

#endif 
