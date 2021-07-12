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
    CanBeClosed = canBeClosed;
    Resized = false;

    glfwSetWindowUserPointer(InternalWindow, this);
    glfwSetFramebufferSizeCallback(InternalWindow, GlfwCallbackResizeFunction);

    LOG_DEBUG("Window has been constructed!");
}

Window::~Window()
{
    LOG_DEBUG("Destroying window...");

    glfwDestroyWindow(InternalWindow);
    glfwTerminate();

    LOG_DEBUG("Window has been destroyed!");
}

bool Window::IsClosingRequested() const
{
    if (!CanBeClosed)
        return false;

    return glfwWindowShouldClose(InternalWindow);
}

void Window::Update() const
{
    if (IsClosingRequested())
        return;

    glfwPollEvents();
}

int Window::GetWidth() const
{
    return WindowWidth;
}

int Window::GetHeight() const
{
    return WindowHeight;
}

void Window::UpdateSize()
{
    do
    {
        glfwGetFramebufferSize(InternalWindow, &WindowWidth, &WindowHeight);
        glfwWaitEvents();
    } while (WindowWidth == 0 || WindowHeight == 0);
}

bool Window::HasBeenResized() const
{
    return Resized;
}

void Window::ResetResized()
{
    Resized = false;
}

std::vector<const char*> Window::GetRequiredExtensions() const
{
    uint32_t extensionsCount = 0;
    const char** extensions;

    extensions = glfwGetRequiredInstanceExtensions(&extensionsCount);

    return std::vector<const char*>(extensions, extensions + extensionsCount);
}

GLFWwindow* Window::GetRaw() const
{
    return InternalWindow;
}

void Window::GlfwCallbackResizeFunction(GLFWwindow* window, const int width, const int height)
{
    auto thisWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    thisWindow->Resized = true;
}