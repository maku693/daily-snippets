#include <windows.h>
#include <tchar.h>

struct State {
    int value;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
    auto hMonitor = MonitorFromWindow(
        NULL, MONITOR_DEFAULTTOPRIMARY
    );

    MONITORINFO monitorInfo {};
    monitorInfo.cbSize = sizeof(MONITORINFO);

    auto monitorInfoAquisionStatus = GetMonitorInfo(
        hMonitor, &monitorInfo
    );

    if (!monitorInfoAquisionStatus) {
        return 0;
    }

    WNDCLASS wndClass {};
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = (WNDPROC)WndProc;
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszClassName = _TEXT("daily-snippet");

    auto wndClassIdentifier = RegisterClass(&wndClass);

    if (!wndClassIdentifier) {
        return 0;
    }

    auto hWnd = CreateWindow(
        MAKEINTATOM(wndClassIdentifier),
        _TEXT("daily-snippet"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        720,
        480,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd) {
        return 0;
    }

    RAWINPUTDEVICE rawMouse {};
    rawMouse.usUsagePage = 1;
    rawMouse.usUsage = 2;
    rawMouse.hwndTarget = hWnd;

    RAWINPUTDEVICE rawKey {};
    rawKey.usUsagePage = 1;
    rawKey.usUsage = 6;
    rawKey.hwndTarget = hWnd;

    RAWINPUTDEVICE rawInputDevices[] = { rawMouse, rawKey };

    auto deviceRegistrationStatus = RegisterRawInputDevices(
        rawInputDevices, 1, sizeof(RAWINPUTDEVICE)
    );

    if (!deviceRegistrationStatus) {
        return 0;
    }

    State state {};

    SetWindowLongPtr(
        hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&state)
    );

    ShowWindow(hWnd, nCmdShow);

    MSG msg {};

    while (true) {
        // Process messages in the queue until it becomes empty
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
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
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
)
{
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    auto state = reinterpret_cast<State*>(
        GetWindowLongPtr(hWnd, GWLP_USERDATA)
    );

    if (uMsg == WM_INPUT) {
        auto handle = reinterpret_cast<HRAWINPUT>(lParam);
        RAWINPUT input {};
        UINT dataSize = sizeof(RAWINPUT);
        UINT headerSize = sizeof(RAWINPUTHEADER);

        auto rawInputDataAquisionStatus = GetRawInputData(
            handle, RID_INPUT, &input, &dataSize, headerSize
        );

        if (rawInputDataAquisionStatus == -1) {
            return 0;
        }

        if (input.header.dwType == RIM_TYPEMOUSE) {
            auto x = input.data.mouse.lLastX;
            auto y = input.data.mouse.lLastY;
            // Dispatch a message here
            return 0;
        }

        if (input.header.dwType == RIM_TYPEKEYBOARD) {
            auto vk = input.data.keyboard.VKey;
            // Dispatch a message here
            return 0;
        }

        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
