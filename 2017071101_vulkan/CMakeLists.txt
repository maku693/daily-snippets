cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project("2017070901" CXX)

include("./FindVulkan.cmake")

find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} WIN32 main.cpp)

target_include_directories(${PROJECT_NAME}
  SYSTEM PUBLIC ${Vulkan_INCLUDE_DIRS}
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(${PROJECT_NAME}
  ${Vulkan_LIBRARY}
  )

target_compile_definitions(${PROJECT_NAME} PRIVATE
  "UNICODE"
  "_UNICODE"
  "VK_USE_PLATFORM_WIN32_KHR"
  )
