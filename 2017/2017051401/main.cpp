#include <windows.h>
#include <tchar.h>

#include <vulkan/vulkan.hpp>

struct AppState {
    bool isActive;
    bool isResumed;
};

struct Curosor {
    bool isLocked;
};

struct RawHIDRegisterer {
public:
    enum class State {
        Ok,
        Error,
    };

    enum class Usage : USHORT {
        Mouse = 2,
    }

    RawHIDRegisterer(Usage usage)
        :m_state(State::Ok)
        ,m_usage(usage)
    {
        RAWINPUTDEVICE rid {};
        rid.usUsagePage = static_cast<USHORT>(1);
        rid.usUsage = static_cast<USHORT>(this->m_usage);
        rid.dwFlags = RIDEV_NOLEGACY;
        rid.hwndTarget = NULL;
        auto success =
            RegisterRawInputDevices({ rid }, 1, sizeof(RAWINPUTDEVICE));
        if (!success) {
            this->m_state = State::Error;
        }
    }

    ~RawInputDeviceRegisterer()
    {
        RAWINPUTDEVICE rid {};
        rid.usUsagePage = static_cast<USHORT>(1);
        rid.usUsage = static_cast<USHORT>(this->m_usage);
        rid.dwFlags = REMOVE;
        rid.hwndTarget = NULL;
        RegisterRawInputDevices({ rid }, 1, sizeof(RAWINPUTDEVICE));
    }

    constexpr State getState() const
    {
        return m_state;
    }

private:
    State m_state;
    Usage m_usage;
};

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
        720,
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

    if (uMsg == WM_SETCURSOR) {
        RECT rc {};
        GetClientRect(hwnd, &rc);
        MapWindowPoints(hwnd, nullptr, reinterpret_cast<LPPOINT>(&rc), 2);
        SetCursor(nullptr); // Hide the cursor
        return TRUE;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
