#include <windows.h>
#include <tchar.h>

struct State {
    int value = 0;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
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
        nullptr
    );

    if (hwnd == nullptr) {
        return 0;
    }

    RAWINPUTDEVICE rid {};
    rid.usUsagePage = 1;
    rid.usUsage = 2;
    rid.hwndTarget = hwnd;

    if (!RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE))) {
        return 0;
    }

    State state {};

    SetWindowLongPtr(
        hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&state)
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};

    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
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
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    State* state;

    state = reinterpret_cast<State*>(
        GetWindowLongPtr(hwnd, GWLP_USERDATA)
    );

    if (uMsg == WM_INPUT) {
        auto handle = reinterpret_cast<HRAWINPUT>(lParam);
        RAWINPUT input {};
        UINT cbSize = sizeof(RAWINPUT);
        UINT cbSizeHeader = sizeof(RAWINPUTHEADER);
        GetRawInputData(handle, RID_INPUT, &input, &cbSize, cbSizeHeader);
        if (input.header.dwType == RIM_TYPEMOUSE) {
            LONG x = input.data.mouse.lLastX;
            LONG y = input.data.mouse.lLastY;
            int dummy = 0; // Breakpoint here
        }

        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
