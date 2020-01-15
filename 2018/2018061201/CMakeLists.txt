cmake_minimum_required(VERSION 3.11)

project(window-test CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} WIN32 src/main.cpp)
