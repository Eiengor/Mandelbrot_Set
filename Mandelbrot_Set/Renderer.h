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
    int screenWidth, screenHeight;

public:
    Renderer(int screenWidth, int screenHeight);

    void render(VAO& vao, Texture& mandelbrotTexture, Shader& displayShader,
        ComputeShader& computeShader, float& zoom, float& center_x, float& center_y);
    void clear(VAO& vao, VBO& vbo, EBO& ebo, Texture& mandelbrotTexture,
        Shader& displayShader, ComputeShader& computeShader);
};

#endif 
