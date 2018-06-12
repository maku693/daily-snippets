#include <Windows.h>

LRESULT CALLBACK wndproc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int) {
    HMONITOR hm = MonitorFromWindow(nullptr, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi = {};
    mi.cbSize = sizeof(MONITORINFO);

    if (!GetMonitorInfoW(hm, &mi)) {
        return 1;
    }

    const auto class_name = L"main";
    WNDCLASSEX wcex{};
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)wndproc;
    wcex.hInstance = hInstance;
    wcex.hCursor = nullptr;
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszClassName = class_name;

    if (!RegisterClassExW(&wcex)) {
        return 1;
    }

    HWND hwnd = CreateWindowExW(
        0,
        class_name,
        L"window-test",
        WS_POPUP | WS_VISIBLE,
        mi.rcMonitor.left,
        mi.rcMonitor.top,
        mi.rcMonitor.right,
        mi.rcMonitor.bottom,
        nullptr,
        nullptr,
        hInstance,
        0
    );
}

LRESULT CALLBACK wndproc(
    HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam
)
{
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    if (uMsg == WM_SETCURSOR) {
        SetCursor(nullptr); // Hide the cursor
        return TRUE;
    }

    return DefWindowProc(hwnd, umsg, wparam, lparam);
}
