﻿#include <windows.h>

#include <vulkan/vulkan.hpp>

#include <algorithm>
#include <cstdint>
#include <functional>
#include <vector>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND createWindow(HINSTANCE);
vk::UniqueInstance createInstance();
vk::UniqueSurfaceKHR createSurface(HINSTANCE, HWND, const vk::UniqueInstance&);
vk::PhysicalDevice pickPhysicalDevice(const vk::UniqueInstance&);
bool isSuitable(const vk::PhysicalDevice&);
vk::UniqueSwapchainKHR createSwapChain(const vk::PhysicalDevice);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    const auto hWnd = createWindow(hInstance);
    const auto instance = createInstance();
    const auto surface = createSurface(hInstance, hWnd, instance);
    const auto physicalDevice = pickPhysicalDevice(instance);

    const auto physicalDevices = instance->enumeratePhysicalDevices();

    if (physicalDevices.size() == 0) {
        throw std::runtime_error("No physical device");
    }

    uint32_t graphicsQueueFamilyIndex;
    uint32_t surfaceQueueFamilyIndex;

    // Find a prop which has graphics queue flag
    const auto graphicsDevice
        = std::find_if(physicalDevices.cbegin(), physicalDevices.cend(),
            [&graphicsQueueFamilyIndex](const auto& device) {
                const auto propsList = device.getQueueFamilyProperties();
                const auto props = std::find_if(propsList.cbegin(),
                    propsList.cend(), [](const auto& props) {
                        return props.queueFlags & vk::QueueFlagBits::eGraphics;
                    });

                // Set the index of queue to use later
                graphicsQueueFamilyIndex
                    = static_cast<uint32_t>(props - propsList.cbegin());

                if (props == propsList.cend()) {
                    throw std::runtime_error("No graphics device");
                }

                return true;
            });

    if (graphicsDevice == physicalDevices.cend()) {
        return 0;
    }

    const auto separatePresentQueue = graphicsDevice->getSurfaceSupportKHR(
        graphicsQueueFamilyIndex, *surface);

    if (separatePresentQueue) {
        surfaceQueueFamilyIndex = graphicsQueueFamilyIndex;
    } else {
        const auto propsList = graphicsDevice->getQueueFamilyProperties();
        for (size_t i = 0; i < propsList.size(); i++) {
            const auto supportsSurface
                = graphicsDevice->getSurfaceSupportKHR(i, *surface);

            if (!supportsSurface) {
                if (i + 1 == propsList.size()) {
                    throw std::runtime_error("No surface support");
                }
                continue;
            }
            surfaceQueueFamilyIndex = i;
        }
    }

    const auto sharingMode = ([&separatePresentQueue]() {
        if (separatePresentQueue) {
            return vk::SharingMode::eExclusive;
        }
        return vk::SharingMode::eConcurrent;
    })();

    const auto queueFamilyIndices = ([&sharingMode, &graphicsQueueFamilyIndex,
        &surfaceQueueFamilyIndex]() {
        using ReturnType = std::vector<uint32_t>;
        if (sharingMode == vk::SharingMode::eExclusive) {
            return ReturnType{};
        }
        return ReturnType{ graphicsQueueFamilyIndex, surfaceQueueFamilyIndex };
    })();

    const auto queueCreateInfo
        = vk::DeviceQueueCreateInfo()
              .setQueueFamilyIndex(graphicsQueueFamilyIndex)
              .setQueueCount(1);
    const auto deviceCreateInfo = vk::DeviceCreateInfo()
                                      .setQueueCreateInfoCount(1)
                                      .setPQueueCreateInfos(&queueCreateInfo);

    const auto device = graphicsDevice->createDeviceUnique(deviceCreateInfo);

    const auto commandPoolCreateInfo
        = vk::CommandPoolCreateInfo().setQueueFamilyIndex(
            graphicsQueueFamilyIndex);

    const auto commandPool
        = device->createCommandPoolUnique(commandPoolCreateInfo);

    const auto commandBufferAllocateInfo
        = vk::CommandBufferAllocateInfo()
              .setCommandPool(*commandPool)
              .setLevel(vk::CommandBufferLevel::ePrimary)
              .setCommandBufferCount(1);

    const auto commandBuffers
        = device->allocateCommandBuffersUnique(commandBufferAllocateInfo);

    const auto surfaceFormats = graphicsDevice->getSurfaceFormatsKHR(*surface);

    if (surfaceFormats.size() == 0) {
        throw std::runtime_error("No surface formats");
    }

    const auto surfaceFormat = std::find_if(surfaceFormats.cbegin(),
        surfaceFormats.cend(), [](const auto& surfaceFormat) {
            if (surfaceFormat.format == vk::Format::eB8G8R8A8Unorm) {
                return true;
            }
            return false;
        });

    if (surfaceFormat == surfaceFormats.cend()) {
        throw std::runtime_error("No appropreate surface format");
    }

    const auto surfaceCapabilities
        = graphicsDevice->getSurfaceCapabilitiesKHR(*surface);

    uint32_t maxImageCount = 3;
    if (surfaceCapabilities.maxImageCount < maxImageCount) {
        maxImageCount = surfaceCapabilities.maxImageCount;
    }

    const auto swapChainExtent = ([&hWnd, &surfaceCapabilities]() {
        if (surfaceCapabilities.currentExtent.width == 0xFFFFFFFF) {
            RECT rect;
            const auto res = GetWindowRect(hWnd, &rect);

            if (!res) {
                throw std::runtime_error("Window rect acquision failed");
            }

            return vk::Extent2D()
                .setWidth(rect.right - rect.left)
                .setHeight(rect.bottom - rect.top);
        }
        return surfaceCapabilities.currentExtent;
    })();

    const auto preTransform = ([&surfaceCapabilities]() {
        if (surfaceCapabilities.supportedTransforms
            & vk::SurfaceTransformFlagBitsKHR::eIdentity) {
            return vk::SurfaceTransformFlagBitsKHR::eIdentity;
        }
        return surfaceCapabilities.currentTransform;
    })();

    const auto compositeAlpha = ([&surfaceCapabilities]() {
        const std::vector<vk::CompositeAlphaFlagBitsKHR> compositeAlphaFlags
            = { vk::CompositeAlphaFlagBitsKHR::eOpaque,
                vk::CompositeAlphaFlagBitsKHR::ePostMultiplied,
                vk::CompositeAlphaFlagBitsKHR::ePreMultiplied,
                vk::CompositeAlphaFlagBitsKHR::eInherit };
        const auto& supported = surfaceCapabilities.supportedCompositeAlpha;

        for (const auto& flag : compositeAlphaFlags) {
            if (supported & flag) {
                return flag;
            }
        }
    })();

    const auto swapchainCreateInfo
        = vk::SwapchainCreateInfoKHR()
              .setSurface(*surface)
              .setMinImageCount(maxImageCount)
              .setImageColorSpace(vk::ColorSpaceKHR::eSrgbNonlinear)
              .setImageFormat(surfaceFormat->format)
              .setImageExtent(swapChainExtent)
              .setImageArrayLayers(1)
              .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
              .setImageSharingMode(sharingMode)
              .setQueueFamilyIndexCount(queueFamilyIndices.size())
              .setPQueueFamilyIndices(queueFamilyIndices.data())
              .setPreTransform(preTransform)
              .setCompositeAlpha(compositeAlpha)
              .setPresentMode(vk::PresentModeKHR::eFifo)
              .setClipped(true);

    const auto swapchain
        = device->createSwapchainKHRUnique(swapchainCreateInfo);

    const auto images = device->getSwapchainImagesKHR(*swapchain);
    const auto buffers = ([&device, &surfaceFormat, &images]() {
        std::vector<vk::UniqueImageView> buffers;
        buffers.resize(images.size());

        for (const auto& image : images) {
            const auto components = vk::ComponentMapping()
                                        .setR(vk::ComponentSwizzle::eR)
                                        .setG(vk::ComponentSwizzle::eG)
                                        .setB(vk::ComponentSwizzle::eB)
                                        .setA(vk::ComponentSwizzle::eA);
            const auto subresourceRange
                = vk::ImageSubresourceRange()
                      .setAspectMask(vk::ImageAspectFlagBits::eColor)
                      .setBaseMipLevel(0)
                      .setLevelCount(1)
                      .setBaseArrayLayer(0)
                      .setLayerCount(1);
            const auto createInfo = vk::ImageViewCreateInfo()
                                        .setImage(image)
                                        .setViewType(vk::ImageViewType::e2D)
                                        .setFormat(surfaceFormat->format)
                                        .setComponents(components)
                                        .setSubresourceRange(subresourceRange);
            auto imageView = device->createImageViewUnique(createInfo);
            buffers.push_back(std::move(imageView));
        }

        return buffers;
    })();

    const auto depthFormat = vk::Format::eD32Sfloat;
    const auto depthFormatProps
        = graphicsDevice->getFormatProperties(depthFormat);
    const auto depthTiling = ([&depthFormatProps]() {
        const auto desiredTilingFeature
            = vk::FormatFeatureFlagBits::eDepthStencilAttachment;
        if (depthFormatProps.linearTilingFeatures & desiredTilingFeature) {
            return vk::ImageTiling::eLinear;
        }
        if (depthFormatProps.optimalTilingFeatures & desiredTilingFeature) {
            return vk::ImageTiling::eOptimal;
        }
        throw std::runtime_error("No 32bit float depth support");
    })();

    const auto depthExtent = vk::Extent3D()
                                 .setWidth(swapChainExtent.width)
                                 .setHeight(swapChainExtent.height)
                                 .setDepth(1);
    const auto depthImageCreateInfo
        = vk::ImageCreateInfo()
              .setImageType(vk::ImageType::e2D)
              .setFormat(depthFormat)
              .setExtent(depthExtent)
              .setMipLevels(1)
              .setArrayLayers(1)
              .setSamples(vk::SampleCountFlagBits::e1)
              .setInitialLayout(vk::ImageLayout::eUndefined)
              .setUsage(vk::ImageUsageFlagBits::eDepthStencilAttachment)
              .setSharingMode(vk::SharingMode::eExclusive);


    ShowWindow(hWnd, SW_SHOWDEFAULT);

    MSG msg{};

    while (true) {
        if (!PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            // Do main stuff here
            continue;
        }

        if (msg.message == WM_QUIT) {
            break;
        }

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return static_cast<int>(msg.wParam);
}

HWND createWindow(HINSTANCE hInstance)
{
    WNDCLASS wndClass{};
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wndClass.hbrBackground
        = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wndClass.lpszClassName = L"daily-snippet";

    const auto atom = RegisterClassW(&wndClass);

    if (!atom) {
        throw std::runtime_error("Window class registration failed");
    }

    auto hWnd = CreateWindow(MAKEINTATOM(atom), L"daily-snippet",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 720, 480, nullptr,
        nullptr, hInstance, nullptr);

    if (!hWnd) {
        throw std::runtime_error("Window creation failed");
    }

    return hWnd;
}

vk::UniqueInstance createInstance()
{
    const auto applicationInfo
        = vk::ApplicationInfo().setApiVersion(VK_API_VERSION_1_0);

    std::vector<const char*> extensionNames = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
    };

    const auto instanceCreateInfo
        = vk::InstanceCreateInfo()
        .setPApplicationInfo(&applicationInfo)
        .setEnabledExtensionCount(
            static_cast<uint32_t>(extensionNames.size()))
        .setPpEnabledExtensionNames(extensionNames.data());

    return vk::createInstanceUnique(instanceCreateInfo);
}

vk::UniqueSurfaceKHR createSurface(HINSTANCE hInstance, HWND hWnd, const vk::UniqueInstance& instance)
{
    const auto surfaceCreateInfo
        = vk::Win32SurfaceCreateInfoKHR().setHinstance(hInstance).setHwnd(hWnd);

    return instance->createWin32SurfaceKHRUnique(surfaceCreateInfo);
}

vk::PhysicalDevice pickPhysicalDevice(const vk::UniqueInstance& instance)
{
    const auto physicalDevices = instance->enumeratePhysicalDevices();

    if (physicalDevices.size() == 0) {
        throw std::runtime_error("No physical device");
    }

    for (const auto& physicalDevice : physicalDevices) {
        if (isSuitable(physicalDevice)) {
            return physicalDevice;
        }
    }

    throw std::runtime_error("No graphics device");
}

bool isSuitable(const vk::PhysicalDevice& device)
{
    const auto propsList = device.getQueueFamilyProperties();
    for (const auto& props : propsList) {
        return static_cast<bool>(props.queueFlags & vk::QueueFlagBits::eGraphics);
    }

    return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
