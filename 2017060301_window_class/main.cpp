#include <windows.h>

#include "application.hpp"
#include "window.hpp"

template <class T>
int ApplicationMain(T state, HINSTANCE hInstance)
{
    Application<T> application{ state, hInstance };
    return application.run();
}

struct state { int i = 0; };

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
    return ApplicationMain(state, hInstance);
}
