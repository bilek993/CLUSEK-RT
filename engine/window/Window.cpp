//
// Created by jbili on 02.04.2021.
//

#include <engine/common/debug/Logger.h>
#include "Window.h"

Window::Window(const int width, const int height, const bool resizable, const bool fullscreen, const bool canBeClosed,
               const std::string& name)
{
    LOG_DEBUG("Constructing new window...");

    if (glfwInit() == GLFW_FALSE)
        throw std::runtime_error("Failed to initialize GLFW!");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);

    InternalWindow = glfwCreateWindow(width,
                                      height,
                                      name.c_str(),
                                      fullscreen ? glfwGetPrimaryMonitor() : nullptr,
                                      nullptr);

    WindowWidth = width;
    WindowHeight = height;

    LOG_DEBUG("Window has been constructed!");
}

Window::~Window()
{
    LOG_DEBUG("Destroying window...");

    glfwDestroyWindow(InternalWindow);
    glfwTerminate();

    LOG_DEBUG("Window has been destroyed!");
}
