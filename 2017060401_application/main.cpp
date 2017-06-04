#include <windows.h>

#include "application.hpp"

struct State { int i = 0; };

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
    Application application{ hInstance };
    State state{};
    // TODO: Inject state update method to main loop
    return application.run();
}
