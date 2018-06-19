#include <Windows.h>
#include <string_view>
#include <winrt/base.h>

class win32_window {
public:
  win32_window();

  HWND native_handle() const { return native_handle_; }

private:
  HWND native_handle_;
  static constexpr wchar_t *class_name = L"main";
  static LRESULT CALLBACK wndproc(HWND, UINT, WPARAM, LPARAM);
};

win32_window::win32_window() {
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
  native_handle_ = ::CreateWindowExW(
      0, class_name, nullptr, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hinstance, nullptr);
  winrt::check_bool(native_handle_);
}

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE, PWSTR, int) {
  const auto class_name = L"main";
  WNDCLASSEXW wcex{};
  wcex.cbSize = sizeof(WNDCLASSEXW);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = wndproc;
  wcex.hInstance = hinstance;
  wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
  wcex.lpszClassName = class_name;

  if (!RegisterClassExW(&wcex)) {
    return HRESULT_FROM_WIN32(GetLastError());
  }

  auto hwnd =
      CreateWindowExW(0, class_name, L"window-test", WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                      CW_USEDEFAULT, nullptr, nullptr, hinstance, nullptr);
  ShowWindow(hwnd, SW_SHOWDEFAULT);

  MSG msg{};
  bool continueRunning = true;
  while (continueRunning) {
    while (PeekMessageW(&msg, hwnd, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
      if (msg.message == WM_QUIT) {
        continueRunning = false;
      }
    }
  }

  return msg.wParam;
}

LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  if (msg == WM_DESTROY) {
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProcW(hwnd, msg, wparam, lparam);
}
