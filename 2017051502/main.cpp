#include <windows.h>
#include <tchar.h>

#include <iostream>

struct Test {
    int value = 100;

    void printValue()
    {
        std::cout << value << std::endl;
    }
};

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
    // Register / create a window
    WNDCLASS wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = _TEXT("GetSetWindowLongPtrTest");

    auto wcIdentifier = RegisterClass(&wc);

    if (!wcIdentifier) {
        return 0;
    }

    Test t{};

    auto hwnd = CreateWindow(
        MAKEINTATOM(wcIdentifier),
        _TEXT("GetSetWindowLongPtrTest"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        &t
    );

    t.value = 200;

    if (!hwnd) {
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
    Test *test;

    if (uMsg == WM_CREATE) {
        LPCREATESTRUCT lpCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        test = reinterpret_cast<Test *>(lpCreateStruct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(test));
        return 0;
    }

    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    test = reinterpret_cast<Test *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    if (test) {
        test->printValue();
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

