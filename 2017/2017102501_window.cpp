#define WIN32_LEAN_AND_MEAN
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow)
{
    WNDCLASSW wndClass {};
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wndClass.hbrBackground = reinterpret_cast<HBRUSH>(
        GetStockObject(BLACK_BRUSH)
    );
    wndClass.lpszClassName = L"window";

    if (!RegisterClassW(&wndClass)) {
        return 0;
    }

    auto hWnd = CreateWindowW(
        L"window",
        L"window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hWnd) {
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);

    MSG msg {};

    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
)
{
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    // TODO: custom message
    if (uMsg == WM_PAINT) {
        OutputDebugStringW(L"Hello");
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
