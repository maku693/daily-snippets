#include <windows.h>

#include <vulkan/vulkan.hpp>

#include <cstdint>

#include "WindowsHelper.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    const auto hWnd = WindowsHelper::createWindow(hInstance);

    // - Initialize vulkan...
    // - Create an instance
    // - Create surface
    // - Set gpu and queue family index for graphics and presenting
    //     - Enumerate GPU and create array of struct with gpu index,
    //       queue family index, is surface supported and score
    //         score = 0 and return unless Graphics is supported
    //         else
    //             score += 1
    //         score += 10 if GPU is Descrete
    //         check if surface is supported
    //     - Sort array by score and pick grapihcs GPU and graphics queue family
    //       index
    //     - If current queue family index doesn't supports surface
    //       pick first queue family index of current GPU for presenting
    // - Throw unless both graphics and presentation supported
    // - Create device
    //     - Set device queue
    // - Create command pool
    // - Create swapchain
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

