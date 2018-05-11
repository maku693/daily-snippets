#pragma once

#include <windows.h>

class Window {
public:
    Window(HINSTANCE) noexcept;

    HWND getHWnd() noexcept;

    void display() noexcept;

    void update() noexcept;

private:
    HWND m_hWnd;

    static LRESULT CALLBACK WndProc;
};
