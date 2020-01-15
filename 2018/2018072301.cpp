#pragma once

#include <cstddef>
#include <vector>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Storage.h>

class AssetLibrary {
public:
  AssetLibrary(const winrt::Windows::Storage::StorageFolder&);

  winrt::Windows::Foundation::IAsyncOperation<std::vector<std::byte>>
      Load(const winrt::hstring&);

private:
  const winrt::Windows::Storage::StorageFolder root_;
};

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;

AssetLibrary::AssetLibrary(
    const StorageFolder &root = Package::Current().InstalledLocation())
    : root_(root) {}

IAsyncOperation<std::vector<std::byte>>
AssetLibrary::Load(const hstring &name) {
  const auto file = co_await root_.GetFileAsync(name);
  const auto buf = co_await FileIO::ReadBufferAsync(file);
  std::vector<std::byte> data(buf.Length());
  DataReader::FromBuffer(buf).ReadBytes(data);
  co_return data;
}
