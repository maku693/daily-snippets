#include <windows.h>
#include <tchar.h>

#include <vulkan/vulkan.hpp>

#include <algorithm>
#include <cstdint>
#include <functional>

class Defer {
public:
    using DeferedT = std::function<void()>;
    explicit Defer(DeferedT&& defered) noexcept
        : m_defered(std::forward<DeferedT>(defered))
    { }

    ~Defer() noexcept(noexcept(this->m_defered()))
    {
        this->m_defered();
    }

private:
    DeferedT m_defered;
};

// ----------

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
    const auto applicationInfo = vk::ApplicationInfo()
        .setApiVersion(VK_API_VERSION_1_0);

    std::vector<const char*> extensionNames = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
    };

    const auto instanceCreateInfo = vk::InstanceCreateInfo()
        .setPApplicationInfo(&applicationInfo)
        .setEnabledExtensionCount(
            static_cast<uint32_t>(extensionNames.size())
        )
        .setPpEnabledExtensionNames(extensionNames.data());

    const auto instance = vk::createInstance(instanceCreateInfo);
    const auto finalizeInstance = Defer(
        [&instance](){ instance.value.destroy(); });

    if (instance.result != vk::Result::eSuccess) {
        return 0;
    }

    WNDCLASS wndClass{};
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wndClass.hbrBackground = reinterpret_cast<HBRUSH>(
        GetStockObject(BLACK_BRUSH)
    );
    wndClass.lpszClassName = _TEXT("daily-snippet");

    auto wndClassIdentifier = RegisterClass(&wndClass);

    if (!wndClassIdentifier) {
        return 0;
    }

    auto hWnd = CreateWindow(
        MAKEINTATOM(wndClassIdentifier),
        _TEXT("daily-snippet"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        720,
        480,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hWnd) {
        return 0;
    }

    const auto surfaceCreateInfo = vk::Win32SurfaceCreateInfoKHR()
        .setHinstance(hInstance)
        .setHwnd(hWnd);

    const auto surface = instance.value
        .createWin32SurfaceKHR(surfaceCreateInfo);

    const auto physicalDevices = instance.value.enumeratePhysicalDevices();

    if (physicalDevices.result != vk::Result::eSuccess) {
        return 0;
    }

    if (physicalDevices.value.size() == 0) {
        return 0;
    }

    uint32_t graphicsQueueFamilyIndex;
    // Find a prop which has graphics queue flag
    const auto graphicsDevice = std::find_if(
        physicalDevices.value.cbegin(), physicalDevices.value.cend(),
        [&surface, &graphicsQueueFamilyIndex](const auto& device)
        {
            const auto propsList = device.getQueueFamilyProperties();
            const auto props = std::find_if(
                propsList.cbegin(), propsList.cend(),
                [](const auto& props)
                {
                    return props.queueFlags & vk::QueueFlagBits::eGraphics;
                }
            );

            // Set the index of queue to use later
            graphicsQueueFamilyIndex =
                static_cast<uint32_t>(props - propsList.begin());

            if (props == propsList.cend()) {
                return false;
            }

            return true;
        }
    );

    if (graphicsDevice == physicalDevices.value.cend()) {
        return 0;
    }

    const auto supportsSurface = graphicsDevice
        ->getSurfaceSupportKHR(graphicsQueueFamilyIndex, surface.value);

    if (supportsSurface.result != vk::Result::eSuccess) {
        return 0;
    }

    const auto surfaceDevice = (
        [&supportSurface, &device]()
        {
            if (supportsSurface.value) {
                return graphicsDevice;
            } else {
                const auto surfaceDevice = std::find_if(
                    physicalDevices.value.cbegin(),
                    physicalDevices.value.cend(),
                    [](const auto& device)
                    {
                        const auto supportsSurface = device
                            .getSurfaceSupportKHR(
                                graphicsQueueFamilyIndex, surface.value
                            );

                        if (supportsSurface.result !=
                            vk::Result::eSuccess) {
                            return false;
                        }

                        if (!supportsSurface.value) {
                            return false;
                        }

                        return true;
                    }
                );

                if (surfaceDevice == physicalDevices.value.cend()) {
                    return 0;
                }
            }
        }
    )();


    // TODO: get presentation device?

    const auto queueCreateInfo = vk::DeviceQueueCreateInfo()
        .setQueueFamilyIndex(graphicsQueueFamilyIndex)
        .setQueueCount(1);
    const auto deviceCreateInfo = vk::DeviceCreateInfo()
        .setQueueCreateInfoCount(1)
        .setPQueueCreateInfos(&queueCreateInfo);

    const auto device = graphicsDevice->createDevice(deviceCreateInfo);
    const auto finalizeDevice = Defer(
        [&device](){ device.value.destroy(); }
    );

    if (device.result != vk::Result::eSuccess) {
        return 0;
    }

    const auto commandPoolCreateInfo = vk::CommandPoolCreateInfo()
        .setQueueFamilyIndex(graphicsQueueFamilyIndex);

    const auto commandPool = device.value
        .createCommandPool(commandPoolCreateInfo);
    const auto finalizeCommandPool = Defer(
        [&device, &commandPool]()
    {
        device.value.destroyCommandPool(commandPool.value);
    }
    );

    if (commandPool.result != vk::Result::eSuccess) {
        return 0;
    }

    const auto commandBufferAllocateInfo = vk::CommandBufferAllocateInfo()
        .setCommandPool(commandPool.value)
        .setLevel(vk::CommandBufferLevel::ePrimary)
        .setCommandBufferCount(1);

    const auto commandBuffer = device.value
        .allocateCommandBuffers(commandBufferAllocateInfo);
    const auto finalizeCommandBuffer = Defer(
        [&device, &commandPool, &commandBuffer]()
        {
            device.value
                .freeCommandBuffers(
                    commandPool.value,
                    { commandBuffer.value }
                );
        }
    );

    if (commandBuffer.result != vk::Result::eSuccess) {
        return 0;
    }

    const auto surfaceFormats = graphicsDevice
        ->getSurfaceFormatsKHR(surface.value);

    if (surfaceFormats.value.size() == 0) {
        return 0;
    }

    const auto surfaceFormat = std::find_if(
        surfaceFormats.value.cbegin(), surfaceFormats.value.cend(),
        [](const auto& surfaceFormat)
        {
            if (surfaceFormat.format == vk::Format::eB8G8R8A8Unorm) {
                return true;
            }
            return false;
        }
    );

    if (surfaceFormat == surfaceFormats.value.cend()) {
        return 0;
    }

    const auto surfacePresentModes = graphicsDevice
        ->getSurfacePresentModesKHR(surface.value);
    if (surfacePresentModes.result != vk::Result::eSuccess) {
        return 0;
    }

    const auto surfaceCapabilities = graphicsDevice
        ->getSurfaceCapabilitiesKHR(surface.value);

    const auto swapChainExtent = (
        [&hWnd, &surfaceCapabilities]()
        {
            if (surfaceCapabilities.value.currentExtent.width
                == 0xFFFFFFFF) {
                RECT rect;
                const auto res = GetWindowRect(hWnd, &rect);

                if (!res) {
                    return vk::Extent2D();
                }

                return vk::Extent2D()
                    .setWidth(rect.right - rect.left)
                    .setHeight(rect.bottom - rect.top);
            }
            return surfaceCapabilities.value.currentExtent;
        }
    )();

    const auto swapchainCreateInfo = vk::SwapchainCreateInfoKHR()
        .setSurface(surface.value)
        .setMinImageCount(3)
        //.setImageColorSpace()
        .setImageFormat(surfaceFormat->format)
        .setImageExtent(swapChainExtent)
        //.setImageArrayLayers()
        //.setPreTransform()
        //.setCompositeAlpha()
        //.setPresentMode()
        .setClipped(true);

    // TODO: swapchain must be destroyed manually

    ShowWindow(hWnd, nCmdShow);

    MSG msg {};

    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }
        // Do main stuff here
    }

    return 0;
}

LRESULT CALLBACK WndProc(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
)
{
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
