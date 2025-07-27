#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Renderer.h"
#include <GLFW/glfw3.h>

class InputHandler
{
private:
    float movementSpeed = 0.01f;
    float zoomSpeed = 0.04f;

public:
    void processInput(GLFWwindow* window, Renderer& renderer);
    void setMovementSpeed(float speed) { movementSpeed = speed; }
    void setZoomSpeed(float speed) { zoomSpeed = speed; }
};

#endif // INPUT_HANDLER_H
