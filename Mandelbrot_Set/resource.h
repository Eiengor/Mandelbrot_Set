#ifndef RESOURCE_H
#define RESOURCE_H


float vertices[12] = {
    //    x      y      z   
        -1.0f, -1.0f, -0.0f,
         1.0f,  1.0f, -0.0f,
        -1.0f,  1.0f, -0.0f,
         1.0f, -1.0f, -0.0f
};

unsigned int indices[6] = {
    0, 1, 2,
    0, 3, 1
};

#endif