void register_class() {
  WNDCLASSW wc{};
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = static_cast<WNDPROC>(wndproc);
  wc.hInstance = GetModuleHandleW(nullptr);
  wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
  wc.lpszClassName = window_class_name;

  if (RegisterClassW(&wc)) {
    throw std::runtime_error("Window class registration failed");
  }
}
