#include <windows.h>
#include <chrono>
#include <sstream>

using namespace std::chrono;

high_resolution_clock::time_point last;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
    last = high_resolution_clock::now();

    WNDCLASS wndClass {};
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wndClass.hbrBackground = reinterpret_cast<HBRUSH>(
        GetStockObject(BLACK_BRUSH)
    );
    wndClass.lpszClassName = L"daily-snippet";

    auto wndClassIdentifier = RegisterClass(&wndClass);

    if (!wndClassIdentifier) {
        return 0;
    }

    auto hWnd = CreateWindowW(
        MAKEINTATOM(wndClassIdentifier),
        L"daily-snippet",
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

    while (true) {
        // Process messages in the queue until it becomes empty
        if (!PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            RedrawWindow(hWnd, nullptr, nullptr, RDW_INTERNALPAINT);
            continue;
        }

        if (msg.message == WM_QUIT) {
            break;
        }

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

    if (uMsg == WM_PAINT) {
        auto now = high_resolution_clock::now();
        auto elapsed = duration_cast<microseconds>(now - last);

        std::wstringstream s;
        s << elapsed.count() << std::endl;

        OutputDebugStringW(s.str().data());

        last = now;
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
