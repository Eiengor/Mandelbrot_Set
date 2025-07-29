#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Renderer.h"
#include <GLFW/glfw3.h>

class InputHandler
{
public:
    void processInput(GLFWwindow* window, float& zoom, float& center_x, float& center_y);
};

#endif // INPUT_HANDLER_H
