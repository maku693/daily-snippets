#include <windows.h>
#include <tchar.h>

#include <vulkan/vulkan.hpp>

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
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        640,
        480,
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

    // if (uMsg == WM_SETCURSOR) {
    //     SetCursor(nullptr); // Hide the cursor
    //     return TRUE;
    // }

    if (uMsg == WM_SETFOCUS) {
        // Lock the cursor in the content area of window
        RECT rc {};
        GetClientRect(hwnd, &rc);
        MapWindowPoints(hwnd, nullptr, reinterpret_cast<LPPOINT>(&rc), 2);
        ClipCursor(&rc);
        return 0;
    }

    if (uMsg == WM_KILLFOCUS) {
        // Disable locking of the cursor
        ClipCursor(nullptr);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
