#include "application.hpp"

int Application::run()
{
    MSG msg {};
    while (true) {
        const auto success = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
        if (!success) {
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
        this->update();
    }

    return msg.wParam;
}

void Application::terminate()
{
    PostQuitMessage(0);
}
