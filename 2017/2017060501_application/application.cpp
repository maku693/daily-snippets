#include <windows.h>

#include "application.hpp"

int Application::run(std::function<void()> mainLoop) const
{
    MSG msg {};
    while (true) {
        const auto success = PeekMessageW(
            &msg, nullptr, 0, 0, PM_REMOVE
        );

        if (!success) {
            mainLoop();
            continue;
        }

        if (msg.message == WM_QUIT) {
            break;
        }

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return msg.wParam;
}

void Application::terminate()
{
    PostQuitMessage(0);
}
