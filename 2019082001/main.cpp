#include <Windows.h>
#include <wil/resource.h>
#include <wil/result.h>

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE, PWSTR, int) {
  WNDCLASSEXW wcex;
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
  wcex.hInstance = hinstance;
  wcex.lpszClassName = L"main";
  const auto wc = THROW_IF_WIN32_BOOL_FALSE(RegisterClassExW(&wcex));

  wil::unique_hwnd hwnd(
      CreateWindowExW(0, MAKEINTATOM(wc), nullptr, WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                      CW_USEDEFAULT, nullptr, nullptr, hinstance, nullptr));

  ShowWindow(hwnd.get(), SW_SHOWMAXIMIZED);

  while (1) {
    MSG msg{};
    while (PeekMessageW(&msg, hwnd.get(), 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
      if (msg.message == WM_QUIT) {
        return msg.wParam;
      }
    }
  }

  return 0;
}

LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  if (msg == WM_DESTROY) {
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProcW(hwnd, msg, wparam, lparam);
}