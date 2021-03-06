#include <Windows.h>

LRESULT CALLBACK wndproc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE, PWSTR, int) {
  const auto class_name = L"main";
  WNDCLASSEXW wcex{};
  wcex.cbSize = sizeof(WNDCLASSEXW);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = static_cast<WNDPROC>(wndproc);
  wcex.hInstance = hinstance;
  wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
  wcex.lpszClassName = class_name;

  if (!RegisterClassExW(&wcex)) {
    return GetLastError();
  }

  auto hwnd =
      CreateWindowExW(0, class_name, L"window-test", WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                      CW_USEDEFAULT, nullptr, nullptr, hinstance, nullptr);
  ShowWindow(hwnd, SW_SHOWDEFAULT);

  MSG msg;
  while (true) {
    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
    }
    if (msg.message == WM_QUIT) {
      break;
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
