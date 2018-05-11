cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project("2017052404")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-D_WIN32_WINNT=0x0A00)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} xaudio2)
