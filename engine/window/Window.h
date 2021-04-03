//
// Created by jbili on 02.04.2021.
//

#ifndef CLUSEK_RT_WINDOW_H
#define CLUSEK_RT_WINDOW_H

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int height, bool resizable, bool fullscreen, bool canBeClosed, const std::string& name);
    ~Window();
    Window(const Window& other) = delete;
    Window(Window&& other) noexcept = delete;
    Window& operator=(const Window& other) = delete;
    Window& operator=(Window&& other) noexcept = delete;

    void Update() const;
    [[nodiscard]] bool IsClosingRequested() const;

    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    void UpdateSize();

    [[nodiscard]] bool HasBeenResized() const;
    void ResetResized();
private:
    static void GlfwCallbackResizeFunction(GLFWwindow* window, int width, int height);

    GLFWwindow* InternalWindow;

    bool Resized;

    int WindowWidth;
    int WindowHeight;
    bool CanBeClosed;
};


#endif //CLUSEK_RT_WINDOW_H
