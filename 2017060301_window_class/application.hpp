#pragma once

#include <windows.h>

class Application final {
public:
    Application(T, HINSTANCE);

    std::shared_ptr<Window> getWindow() noexcept;

    int run();
    void terminate();

private:
    std::shared_ptr<Window> m_window;
};
