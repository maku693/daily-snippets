#include <windows.h>

#include "application.hpp"

struct State { int i = 0; };

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    const MainLoop mainLoop{};
    State state{};

    return mainLoop.run([&state]() {
        state.i += 1;
    });
}
