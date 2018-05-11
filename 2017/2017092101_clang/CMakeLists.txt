cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(clang-tidy CXX)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_CXX_COMPILER clang-cl)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE
  "-Werror"
  "-Weverything"
  "-Wno-c++98-compat"
  "-Wno-c++98-compat-pedantic"
  "-fms-compatibility-version=19.10"
  )
