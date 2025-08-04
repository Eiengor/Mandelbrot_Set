#include "InputHandler.h"

void InputHandler::processInput(GLFWwindow* window, float& zoom, float& center_x, float& center_y)
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
        if (center_x < -2.0f)
        {
            center_x = -2.0f;
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