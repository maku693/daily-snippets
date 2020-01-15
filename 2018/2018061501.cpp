#include <Windows.h>
#include <CoreWindow.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>

int main() {
    winrt::init_apartment();

    const auto window = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread();

    const auto core_window_interop = window.as<ICoreWindowInterop>();
    HWND hwnd;
    core_window_interop->get_WindowHandle(&hwnd);
}
