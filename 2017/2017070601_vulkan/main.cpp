#include <windows.h>

#include <vulkan/vulkan.hpp>

#include <array>
#include <cstdint>

#include "WindowsHelper.hpp"
#include "VulkanHelper.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    const auto hWnd = WindowsHelper::createWindow(hInstance);

    // Create an vulkan instance
    const auto applicationInfo
        = vk::ApplicationInfo().setApiVersion(VK_API_VERSION_1_0);

    const std::vector<const char*> extensionNames = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
    };

    const auto instanceCreateInfo =
        vk::InstanceCreateInfo()
        .setPApplicationInfo(&applicationInfo)
        .setEnabledExtensionCount(
            static_cast<uint32_t>(extensionNames.size()))
        .setPpEnabledExtensionNames(extensionNames.data());

    const auto instance = vk::createInstanceUnique(instanceCreateInfo);

    // Create a surface
    const auto surfaceCreateInfo =
        vk::Win32SurfaceCreateInfoKHR().setHinstance(hInstance).setHwnd(hWnd);

    const auto surface =
        instance->createWin32SurfaceKHRUnique(surfaceCreateInfo);

    // Select GPU and queue family index for graphics and presentation
    const auto physicalDevices = instance->enumeratePhysicalDevices();

    if (physicalDevices.size() == 0) {
        throw std::runtime_error("No physical device");
    }

    uint32_t physicalDeviceIndex = UINT32_MAX;
    uint32_t graphicsQueueFamilyIndex = UINT32_MAX;
    uint32_t presentationQueueFamilyIndex = UINT32_MAX;

    for (uint32_t i = 0; i < physicalDevices.size(); i++) {
        const auto& gpu = physicalDevices.at(i);
        const auto props = gpu.getQueueFamilyProperties();
        for (uint32_t j = 0; j < props.size(); j++) {
            if (props.at(i).queueFlags & vk::QueueFlagBits::eGraphics) {
                graphicsQueueFamilyIndex = j;
            }

            if (gpu.getSurfaceSupportKHR(j, *surface)) {
                presentationQueueFamilyIndex = j;
            }
        }

        if (graphicsQueueFamilyIndex != UINT32_MAX &&
            presentationQueueFamilyIndex != UINT32_MAX) {
            physicalDeviceIndex = i;
            break;
        } else {
            // Reset values for next iteration
            graphicsQueueFamilyIndex = UINT32_MAX;
            presentationQueueFamilyIndex = UINT32_MAX;
        }
    }

    if (graphicsQueueFamilyIndex == UINT32_MAX ||
        presentationQueueFamilyIndex == UINT32_MAX) {
        throw std::runtime_error("No both graphics and presentation support");
    }

    const bool separatePresentationQueue
        = graphicsQueueFamilyIndex != presentationQueueFamilyIndex;

    std::vector<uint32_t> queueFamilyIndices;
    if (separatePresentationQueue) {
        queueFamilyIndices.assign(
            { graphicsQueueFamilyIndex, presentationQueueFamilyIndex });
    } else {
        queueFamilyIndices.assign({ graphicsQueueFamilyIndex });
    }

    const auto& gpu = physicalDevices.at(physicalDeviceIndex);

    // Create a device
    auto graphicsQueueCreateInfo =
        vk::DeviceQueueCreateInfo()
        .setQueueFamilyIndex(graphicsQueueFamilyIndex).setQueueCount(1);
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos =
        { std::move(graphicsQueueCreateInfo) };

    if (separatePresentationQueue) {
        auto presentationQueueCreateInfo =
            vk::DeviceQueueCreateInfo()
            .setQueueFamilyIndex(presentationQueueFamilyIndex).setQueueCount(1);
        queueCreateInfos.push_back(std::move(presentationQueueCreateInfo));
    }

    const auto deviceCreateInfo = vk::DeviceCreateInfo()
        .setQueueCreateInfoCount(queueCreateInfos.size())
        .setPQueueCreateInfos(queueCreateInfos.data());

    const auto device = gpu.createDeviceUnique(deviceCreateInfo);

    // Create a swapchain
    bool isSwapchainExtensionSupported = false;
    const auto deviceExtensions = gpu.enumerateDeviceExtensionProperties();

    for (const auto& deviceExtension : deviceExtensions) {
        if (strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME,
                deviceExtension.extensionName)) {
        }
        break;
    }

    const auto surfaceFormats = gpu.getSurfaceFormatsKHR(*surface);

    if (surfaceFormats.size() == 0) {
        throw std::runtime_error("No surface formats");
    }

    const auto surfaceFormatIter = std::find_if(surfaceFormats.cbegin(),
        surfaceFormats.cend(), [](const auto& surfaceFormat) {
            if (surfaceFormat.format == vk::Format::eB8G8R8A8Unorm) {
                return true;
            }
            return false;
        });

    if (surfaceFormatIter == surfaceFormats.cend()) {
        throw std::runtime_error("No appropreate surface format");
    }

    const auto& surfaceFormat = *surfaceFormatIter;

    uint32_t swapchainImageCount = 3;

    const auto surfaceCapabilities = gpu.getSurfaceCapabilitiesKHR(*surface);

    if (surfaceCapabilities.maxImageCount < swapchainImageCount) {
        swapchainImageCount = surfaceCapabilities.maxImageCount;
    }

    const auto windowSize = WindowsHelper::getWindowSize(hWnd);

    const auto swapchainExtent = VulkanHelper::createSwapChainExtent(
        surfaceCapabilities.currentExtent,
        static_cast<uint32_t>(windowSize.cx),
        static_cast<uint32_t>(windowSize.cy));

    vk::SharingMode sharingMode;

    if (separatePresentationQueue) {
        sharingMode = vk::SharingMode::eConcurrent;
    } else {
        sharingMode = vk::SharingMode::eExclusive;
    }

    vk::SurfaceTransformFlagBitsKHR preTransform;

    if (surfaceCapabilities.supportedTransforms &
        vk::SurfaceTransformFlagBitsKHR::eIdentity) {
        preTransform = vk::SurfaceTransformFlagBitsKHR::eIdentity;
    } else {
        preTransform = surfaceCapabilities.currentTransform;
    }

    const auto swapchainCreateInfo
        = vk::SwapchainCreateInfoKHR()
        .setSurface(*surface)
        .setMinImageCount(swapchainImageCount)
        .setImageColorSpace(surfaceFormat.colorSpace)
        .setImageFormat(surfaceFormat.format)
        .setImageExtent(swapchainExtent)
        .setImageArrayLayers(1)
        .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
        .setImageSharingMode(sharingMode)
        .setQueueFamilyIndexCount(queueFamilyIndices.size())
        .setPQueueFamilyIndices(queueFamilyIndices.data())
        .setPreTransform(preTransform)
        .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
        .setPresentMode(vk::PresentModeKHR::eFifo)
        .setClipped(true);

    const auto swapchain
        = device->createSwapchainKHRUnique(swapchainCreateInfo);

    const auto swapchainImages
        = device->getSwapchainImagesKHR(*swapchain);

    std::vector<vk::UniqueImageView> swapchainImageViews;
    swapchainImageViews.reserve(swapchainImages.size());
    for (const auto& image : swapchainImages) {
        const auto subresourceRange
            = vk::ImageSubresourceRange()
                  .setAspectMask(vk::ImageAspectFlagBits::eColor)
                  .setBaseMipLevel(0)
                  .setLevelCount(1)
                  .setBaseArrayLayer(0)
                  .setLayerCount(1);
        const auto imageViewCreateInfo
            = vk::ImageViewCreateInfo()
                  .setImage(image)
                  .setViewType(vk::ImageViewType::e2D)
                  .setFormat(surfaceFormat.format)
                  .setSubresourceRange(subresourceRange);
        swapchainImageViews.push_back(
            device->createImageViewUnique(imageViewCreateInfo));
    }

    // - Create command pool
    // - Create fences for each images of swapchain
    // - Create image aquired semaphore and draw complete semaphore
    //   for each images of swapchain
    // - Create Depth Buffer
    // - Create Frame Buffer
    // - Create Descriptor layouts
    // - Create Render Pass
    //     - Create attachments
    //     - Create subpasses
    // - Create command buffers for each swapchain images
    // - Create pipeline
    //     - set pipeline layout
    // - Set barriers for each render targets
    // - Aquire initial image
    //
    // - Rendering...

    ShowWindow(hWnd, SW_SHOWDEFAULT);

    WindowsHelper::mainLoop();
}

