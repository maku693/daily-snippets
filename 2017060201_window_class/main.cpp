#include <windows.h>

#include "application.hpp"
#include "window.hpp"

int ApplicationMain(HINSTANCE hInstance)
{
    Application application{ hInstance };
    return application.run();
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
    return ApplicationMain(hInstance);
}
