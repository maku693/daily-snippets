#pragma comment(lib, "windowsapp")

#include <CoreWindow.h>
#include <Windows.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>

using namespace winrt;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;

class App : public implements<App, IFrameworkViewSource, IFrameworkView> {
public:
  IFrameworkView CreateView() { return *this; }

  void Initialize(const CoreApplicationView) const {}

  void Load(const winrt::hstring) const {}

  void SetWindow(const CoreWindow &window) const {
    const auto core_window_interop = window.as<ICoreWindowInterop>();
    HWND hwnd{};
    core_window_interop->get_WindowHandle(&hwnd);
  }

  void Run() const {
    const auto window = CoreWindow::GetForCurrentThread();
    window.Activate();

    const auto dispatcher = window.Dispatcher();
    dispatcher.ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
  }

  void Uninitialize() const {}
};

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  CoreApplication::Run(App());
}
