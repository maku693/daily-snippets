#pragma once

class Window {
public:
    Window(HINSTANCE, int) noexcept;

    HWND getHWnd() noexcept;

    void display() noexcept;

    void update() noexcept;

private:
    HWND m_hWnd;

    static LRESULT CALLBACK WndProc;
};
