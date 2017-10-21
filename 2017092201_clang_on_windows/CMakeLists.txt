cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(clang-on-windows CXX)

if (WIN32)
  set(CMAKE_CXX_COMPILER clang-cl)
  # Workaround to avoid an invalid compile option added by CMake
  unset(CMAKE_CXX14_STANDARD_COMPILE_OPTION)
else()
  set(CMAKE_CXX_COMPILER clang++)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE
  "-Werror"
  "-Weverything"
  "-Wno-c++98-compat"
  "-Wno-c++98-compat-pedantic"
  $<$<PLATFORM_ID:WIN32>:"-fms-compatibility-version=19.10">
  )
