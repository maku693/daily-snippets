#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.hpp>

#include <vector>

int main() {
  const vk::ApplicationInfo app_info{};
  std::vector<const char *> layers{"VK_LAYER_LUNARG_standard_validation"};
  std::vector<const char *> extensions{
      VK_KHR_SWAPCHAIN_EXTENSION_NAME, VK_KHR_SURFACE_EXTENSION_NAME,
      VK_KHR_WIN32_SURFACE_EXTENSION_NAME, VK_EXT_DEBUG_UTILS_EXTENSION_NAME};
  const auto instance = vk::createInstance({{},
                                            &app_info,
                                            layers.size(),
                                            layers.data(),
                                            extensions.size(),
                                            extensions.data()});
  instance.destroy();
}
