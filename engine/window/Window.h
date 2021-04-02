//
// Created by jbili on 02.04.2021.
//

#ifndef CLUSEK_RT_WINDOW_H
#define CLUSEK_RT_WINDOW_H


class Window
{
public:
    Window() = default;
    ~Window() = default;
    Window(const Window& other) = delete;
    Window(Window&& other) noexcept = delete;
    Window& operator=(const Window& other) = delete;
    Window& operator=(Window&& other) noexcept = delete;
};


#endif //CLUSEK_RT_WINDOW_H
