//
// Created by jbili on 02.04.2021.
//

#ifndef CLUSEK_RT_WINDOW_H
#define CLUSEK_RT_WINDOW_H

#include <GLFW/glfw3.h>
#include <vector>

class Window final
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

    [[nodiscard]] std::vector<const char*> GetRequiredExtensions() const;

    [[nodiscard]] GLFWwindow* GetRaw() const;

private:
    static void GlfwCallbackResizeFunction(GLFWwindow* window, int width, int height);

    GLFWwindow* InternalWindow;

    bool Resized;

    int WindowWidth;
    int WindowHeight;
    bool CanBeClosed;
};


#endif //CLUSEK_RT_WINDOW_H
