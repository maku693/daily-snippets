#pragma once

#include <vulkan/vulkan.hpp>

#include <cstddef>
#include <limits>

namespace VulkanHelper {

inline vk::Extent2D createSwapChainExtent(vk::Extent2D currentExtent,
    uint32_t fallbackWidth, uint32_t fallbackHeight)
{
    if (currentExtent.width != -1 && currentExtent.height != -1) {
        return currentExtent;
    }

    return { fallbackWidth, fallbackHeight };
}

} // namespace VulkanHelper

