#include "application.hpp"

int Application::run() const
{
    MSG msg {};
    while (true) {
        const auto success = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
        if (!success) {
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

void Application::terminate()
{
    PostQuitMessage(0);
}
