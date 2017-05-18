#include <windows.h>
#include <tchar.h>

struct State {
    int value = 0;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
    State state {};

    // Get primary monitor
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
    wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = _TEXT("daily-snippet");

    ATOM wcIdentifier = RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        MAKEINTATOM(wcIdentifier),
        _TEXT("daily-snippet"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        720,
        480,
        nullptr,
        nullptr,
        hInstance,
        &state
    );

    if (hwnd == nullptr) {
        return 0;
    }

    RAWINPUTDEVICE rid {};
    rid.usUsagePage = static_cast<USHORT>(1);
    rid.usUsage = static_cast<USHORT>(2);

    RAWINPUTDEVICE rids[] = { rid };

    if (!RegisterRawInputDevices(rids, 1, sizeof(RAWINPUTDEVICE))) {
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
        // Do main stuff here
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
)
{
    State* state;

    if (uMsg == WM_CREATE) {
        LPCREATESTRUCT lpCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        state = reinterpret_cast<State*>(lpCreateStruct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(state));
        return 0;
    }

    state = reinterpret_cast<State*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    if (uMsg == WM_SETCURSOR) {
        RECT rc {};
        GetClientRect(hwnd, &rc);
        MapWindowPoints(hwnd, nullptr, reinterpret_cast<LPPOINT>(&rc), 2);
        SetCursor(nullptr); // Hide the cursor
        return TRUE;
    }

    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
