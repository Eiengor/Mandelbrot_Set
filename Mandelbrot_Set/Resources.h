#ifndef RESOURCES_H
#define RESOURCES_H

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
#include "Performance.h"

int screen_width = 1600;
int screen_height = 900;

int num_frames = 0;
float center_x = 0.0f;
float center_y = 0.0f;
float zoom = 1.0f;

float last_time = 0.0f;
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

#endif // !RESOURCES_H

