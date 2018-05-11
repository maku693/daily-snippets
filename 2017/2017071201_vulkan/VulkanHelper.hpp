#pragma once

#include <vulkan/vulkan.hpp>

#include <cstdint>
#include <cstring>

namespace VulkanHelper {

inline bool isInstanceLayerAvailable(const std::vector<const char*>& names)
{
    const auto props = vk::enumerateInstanceLayerProperties();

    return std::all_of(
        names.cbegin(), names.cend(), [&props](const char* name) {
            return std::any_of(
                props.cbegin(), props.cend(), [name](const auto& prop) {
                    return std::strcmp(name, prop.layerName) == 0;
                });
        });
}

inline bool isInstanceExtensionAvailable(const std::vector<const char*>& names)
{
    const auto props = vk::enumerateInstanceExtensionProperties();

    return std::all_of(
        names.cbegin(), names.cend(), [&props](const char* name) {
            return std::any_of(
                props.cbegin(), props.cend(), [name](const auto& prop) {
                    return std::strcmp(name, prop.extensionName) == 0;
                });
        });
}

inline vk::Extent2D createSwapChainExtent(vk::Extent2D currentExtent,
    std::uint32_t fallbackWidth, std::uint32_t fallbackHeight)
{
    if (currentExtent.width != -1 && currentExtent.height != -1) {
        return currentExtent;
    }

    return { fallbackWidth, fallbackHeight };
}


} // namespace VulkanHelper

