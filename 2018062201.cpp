#include <Windows.h>
#include <string_view>
#include <winrt/base.h>

class win32_window {
public:
  win32_window() {
    const HINSTANCE hinstance = ::GetModuleHandleW(nullptr);
    if (!::GetClassInfoExW(hinstance, class_name, nullptr)) {
      WNDCLASSEXW wcex{};
      wcex.cbSize = sizeof(WNDCLASSEXW);
      wcex.style = CS_HREDRAW | CS_VREDRAW;
      wcex.lpfnWndProc = wndproc;
      wcex.hInstance = hinstance;
      // wcex.hbrBackground = BLACK_BRUSH;
      wcex.lpszClassName = class_name;
      winrt::check_bool(::RegisterClassExW(&wcex));
    }
    hwnd =
        ::CreateWindowExW(0, class_name, nullptr, WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, nullptr, nullptr, hinstance, nullptr);
    winrt::check_bool(hwnd);
  }

  void activate() const { ::ShowWindow(hwnd, SW_SHOWDEFAULT); }

  HWND native_handle() const { return hwnd; }

  void process_events() const {
    MSG msg{};
    while (::PeekMessageW(&msg, hwnd, 0, 0, PM_REMOVE)) {
      ::TranslateMessage(&msg);
      ::DispatchMessageW(&msg);
    }
  }

private:
  HWND hwnd;

  static LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wparam,
                                  LPARAM lparam) {
    return DefWindowProcW(hwnd, msg, wparam, lparam);
  }

  static constexpr wchar_t *class_name = L"main";
};

template <class F> int win32_main(F &&func) {
  MSG msg{};
  while (true) {
    func();
    while (::PeekMessageW(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
      if (msg.message == WM_QUIT) {
        return msg.wParam;
      }
    }
  }
}

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE, PWSTR, int) {
  const auto window = win32_window();
  window.activate();
  return win32_main([&window] { window.process_events(); });
}
