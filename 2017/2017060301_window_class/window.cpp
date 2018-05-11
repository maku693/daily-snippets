#include "window.hpp"

Window::Window(HINSTANCE hInstance)
{
    WNDCLASSW wndClass{ };
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(Window::WndProc);
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wndClass.hbrBackground = reinterpret_cast<HBRUSH>(
        GetStockObject(BLACK_BRUSH)
    );

    const auto atom = RegisterClassW(&wndClass);
    if (!atom) {
        throw std::runtime_error("Window class registration failed");
    }

    this->hWnd = CreateWindowW(
        MAKEINTATOM(atom),
        "",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );
}

void Window::display()
{
    ShowWindow(this->hwnd, SW_SHOWDEFAULT);
}

void Window::update()
{
}

static LRESULT CALLBACK Window::WndProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
