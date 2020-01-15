#pragma comment(lib, "windowsapp")

#include <string>
#include <iostream>

#include <winrt/Windows.Foundation.Diagnostics.h>
#include <winrt/Windows.Foundation.Numerics.h>

using namespace std;
using namespace winrt;

using namespace Windows::Foundation::Diagnostics;
using namespace Windows::Foundation::Numerics;

int main() {
  init_apartment();

  const LoggingSession log_sess{L"daily-snippets.windowsnumerics"};
  const LoggingChannel log_chan{L"debug", nullptr};
  log_sess.AddLoggingChannel(log_chan);

  constexpr float4 f4{1, 2, 3, 4};
  std::wcout << L"length_squared: " << to_wstring(length_squared(f4)) << L'\n';
  std::wcout << L"length: " << to_wstring(length(f4)) << L'\n';
}
