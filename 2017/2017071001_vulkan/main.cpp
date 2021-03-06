#include <windows.h>

#include <vulkan/vulkan.hpp>

#include <algorithm>
#include <cstdint>
#include <vector>

#include "WindowsHelper.hpp"
#include "VulkanHelper.hpp"

static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
    VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType,
    std::uint64_t obj, std::size_t location, std::int32_t code,
    const char* layerPrefix, const char* msg, void* userData)
{
    OutputDebugStringA(msg);
    return VK_FALSE;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    const auto hWnd = WindowsHelper::createWindow(hInstance);

    // Create an vulkan instance
    const auto applicationInfo
        = vk::ApplicationInfo().setApiVersion(VK_API_VERSION_1_0);

    const std::vector<const char*> layerNames = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    if (!VulkanHelper::isInstanceLayerAvailable(layerNames)) {
        throw std::runtime_error("Can't find required instance layer");
    }

    const std::vector<const char*> extensionNames
        = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
            VK_EXT_DEBUG_REPORT_EXTENSION_NAME };

    if (!VulkanHelper::isInstanceExtensionAvailable(extensionNames)) {
        throw std::runtime_error("Can't find required instance extension");
    }

    const auto instanceCreateInfo =
        vk::InstanceCreateInfo()
        .setPApplicationInfo(&applicationInfo)
        .setEnabledLayerCount(
            static_cast<std::uint32_t>(layerNames.size()))
        .setPpEnabledLayerNames(layerNames.data())
        .setEnabledExtensionCount(
            static_cast<std::uint32_t>(extensionNames.size()))
        .setPpEnabledExtensionNames(extensionNames.data());

    const auto instance = vk::createInstanceUnique(instanceCreateInfo);

    const auto debugReportCallbackCreateInfo =
        vk::DebugReportCallbackCreateInfoEXT()
        .setFlags(vk::DebugReportFlagBitsEXT::eInformation
            | vk:: DebugReportFlagBitsEXT::eWarning)
        .setPfnCallback(debugCallback);

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

    std::uint32_t physicalDeviceIndex = UINT32_MAX;
    std::uint32_t graphicsQueueFamilyIndex = UINT32_MAX;
    std::uint32_t presentationQueueFamilyIndex = UINT32_MAX;

    for (std::uint32_t i = 0; i < physicalDevices.size(); i++) {
        const auto& gpu = physicalDevices.at(i);
        const auto props = gpu.getQueueFamilyProperties();
        for (std::uint32_t j = 0; j < props.size(); j++) {
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

    std::vector<std::uint32_t> queueFamilyIndices;
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
    const auto deviceExtensionProps = gpu.enumerateDeviceExtensionProperties();

    const bool isSwapchainExtensionSupported = std::any_of(
        deviceExtensionProps.cbegin(), deviceExtensionProps.cend(),
        [](const auto& prop) {
        return std::strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, prop.extensionName)
            == 0;
        });

    if (!isSwapchainExtensionSupported) {
        throw std::runtime_error("No swapchain support");
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

    std::uint32_t swapchainImageCount = 3;

    const auto surfaceCapabilities = gpu.getSurfaceCapabilitiesKHR(*surface);

    if (surfaceCapabilities.maxImageCount < swapchainImageCount) {
        swapchainImageCount = surfaceCapabilities.maxImageCount;
    }

    const auto windowSize = WindowsHelper::getWindowSize(hWnd);

    const auto swapchainExtent = VulkanHelper::createSwapChainExtent(
        surfaceCapabilities.currentExtent,
        static_cast<std::uint32_t>(windowSize.cx),
        static_cast<std::uint32_t>(windowSize.cy));

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

    const auto depthImageCreateInfo
        = vk::ImageCreateInfo()
              .setImageType(vk::ImageType::e2D)
              .setFormat(vk::Format::eD24UnormS8Uint)
              .setExtent({ swapchainExtent.width, swapchainExtent.height, 1 })
              .setMipLevels(1)
              .setArrayLayers(1)
              .setSamples(vk::SampleCountFlagBits::e1)
              .setTiling(vk::ImageTiling::eOptimal)
              .setUsage(vk::ImageUsageFlagBits::eDepthStencilAttachment)
              .setSharingMode(vk::SharingMode::eExclusive)
              .setQueueFamilyIndexCount(0)
              .setPQueueFamilyIndices(nullptr)
              .setInitialLayout(vk::ImageLayout::eUndefined);

    const auto depthImage = device->createImageUnique(depthImageCreateInfo);

    const auto depthImageMemoryRequirements
        = device->getImageMemoryRequirements(*depthImage);

    // const auto depthImageMemoryAllocInfo
    //     = vk::MemoryAllocateInfo()
    //           .setAllocationSize(depthImageMemoryRequirements.size)
    //           .setMemoryTypeIndex()

    // - Create Depth Buffer
    // - Create Uniform buffer
    // - Create fences for each images of swapchain
    // - Create image aquired semaphore and draw complete semaphore
    //   for each images of swapchain
    // - Create pipeline
    //     - set pipeline layout
    // - Create Descriptor layouts
    // - Create Render Pass
    //     - Create attachments
    //     - Create subpasses
    // - Create Frame Buffer
    // - Create command pool
    // - Create command buffers for each swapchain images
    // - Set barriers for each render targets
    // - Aquire initial image
    //
    // - Rendering...

    ShowWindow(hWnd, SW_SHOWDEFAULT);

    WindowsHelper::mainLoop();
}

