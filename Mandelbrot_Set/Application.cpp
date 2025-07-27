#include "Application.h"
#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
using namespace std;

Application::Application(int screenWidth, int screenHeight, const char* title)
    : screenWidth(screenWidth), screenHeight(screenHeight), title(title), window(nullptr)
{
    if (!initialize()) {
        throw runtime_error("Failed to initialize GLFW");
    }
    if (!createWindow()) {
        glfwTerminate();
        throw runtime_error("Failed to create window");
    }
}

Application::~Application()
{
    clear();
}

bool Application::initialize()
{
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW!" << endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return true;
}

bool Application::createWindow()
{
    window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
    if (window == nullptr) {
        cerr << "Failed to create GLFW window!" << endl;
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    glfwSetWindowUserPointer(window, this);

    if (!gladLoadGL()) {
        cerr << "Failed to initialize GLAD!" << endl;
        return false;
    }

    glViewport(0, 0, screenWidth, screenHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return true;
}
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->onFramebufferResize(width, height);
    }
}

void Application::onFramebufferResize(int width, int height)
{
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
}

void Application::beginFrame()
{
    glfwPollEvents();
}
void Application::endFrame()
{
    glfwSwapBuffers(window);
}
void Application::clear()
{
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

bool Application::shouldClose() const
{
    return window ? glfwWindowShouldClose(window) : true;
}

void Application::setShouldClose(bool shouldClose)
{
    if (window) {
        glfwSetWindowShouldClose(window, shouldClose);
    }
}

GLFWwindow* Application::getWindow()
{
    return this->window;
}

int Application::getWidth()
{
    return this->screenWidth;
}

int Application::getHeight()
{
    return this->screenHeight;
}

const char* Application::getTitle()
{
    return this->title;
}