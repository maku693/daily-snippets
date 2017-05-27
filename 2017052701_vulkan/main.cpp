#include <windows.h>
#include <tchar.h>

#include <vulkan/vulkan.hpp>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
    const auto applicationInfo = vk::ApplicationInfo()
        .setApiVersion(VK_API_VERSION_1_0);

    const auto instanceCreateInfo = vk::InstanceCreateInfo()
        .setPApplicationInfo(&applicationInfo);

    const auto instance = vk::createInstance(instanceCreateInfo);

    if (instance.result != vk::Result::eSuccess) {
        instance.value.destroy();
        return 0;
    }

    const auto devices = instance.value.enumeratePhysicalDevices();

    if (devices.result != vk::Result::eSuccess) {
        return 0;
    }

    if (devices.value.size() == 0) {
        return 0;
    }

    WNDCLASS wndClass {};
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wndClass.hbrBackground = reinterpret_cast<HBRUSH>(
        GetStockObject(BLACK_BRUSH)
    );
    wndClass.lpszClassName = _TEXT("daily-snippet");

    auto wndClassIdentifier = RegisterClass(&wndClass);

    if (!wndClassIdentifier) {
        instance.value.destroy();
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
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hWnd) {
        instance.value.destroy();
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);

    MSG msg {};

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

    instance.value.destroy();
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

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
