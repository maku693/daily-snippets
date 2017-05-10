#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
    HMONITOR hm = MonitorFromWindow(nullptr, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi = {};
    mi.cbSize = sizeof(MONITORINFO);

    if (!GetMonitorInfo(hm, &mi)) {
        return 0;
    }

    WNDCLASS wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = nullptr;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = _TEXT("playground");

    ATOM windowClass = RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        MAKEINTATOM(windowClass),
        _TEXT("playground"),
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

    if (hwnd == nullptr) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};

    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT) {
                break;
            }

            continue;
        }
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
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

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
