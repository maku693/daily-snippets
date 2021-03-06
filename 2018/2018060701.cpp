#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.hpp>

#include <vector>

int main() {
  const vk::ApplicationInfo app_info{nullptr, 0, nullptr, 0,
                                     VK_API_VERSION_1_1};
  std::vector<const char *> layers{"VK_LAYER_LUNARG_standard_validation"};
  std::vector<const char *> extensions{VK_EXT_DEBUG_UTILS_EXTENSION_NAME};
  const auto instance = vk::createInstance({{},
                                            &app_info,
                                            layers.size(),
                                            layers.data(),
                                            extensions.size(),
                                            extensions.data()});
  const auto devices = instance.enumeratePhysicalDevices();
  instance.destroy();
}
