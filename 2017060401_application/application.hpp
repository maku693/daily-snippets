#pragma once

#include <windows.h>

class Application final {
public:
    Application(T, HINSTANCE);

    int run();
    void terminate() noexcept;
};
