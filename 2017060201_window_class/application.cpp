#include "application.hpp"

int Application::run()
{
    this->m_shouldKeepRunning = true;

    MSG msg {};
    while (true) {
        const auto success = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
        if (!success) {
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);

        this->updateWindows();
    }

    return msg.wParam;
}

void Application::updateWindows()
{
    for (const auto window : this->m_windows) {
        window->update();
    }
}

void Application::terminate()
{
    PostQuitMessage(0);
}
