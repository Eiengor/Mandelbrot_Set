#include "InputHandler.h"

void InputHandler::processInput(GLFWwindow* window, Renderer& renderer)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    float moveSpeed = movementSpeed * renderer.getZoom();

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        renderer.moveCenter(0.0f, moveSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        renderer.moveCenter(0.0f, -moveSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        renderer.moveCenter(-moveSpeed, 0.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        renderer.moveCenter(moveSpeed, 0.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        renderer.adjustZoom(1.0f + zoomSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        renderer.adjustZoom(1.0f - zoomSpeed);
    }
}