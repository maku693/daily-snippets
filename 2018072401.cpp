#include "pch.h"

#include "AssetsLibrary.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;

AssetLibrary::AssetLibrary(
    const StorageFolder &root = Package::Current().InstalledLocation())
    : root_(root) {}

std::future<std::vector<std::uint8_t>> AssetLibrary::Load(const hstring &name) {
  const auto file = co_await root_.GetFileAsync(name);
  const auto buf = co_await FileIO::ReadBufferAsync(file);
  std::vector<std::uint8_t> data(buf.Length());
  DataReader::FromBuffer(buf).ReadBytes(data);
  co_return data;
}
