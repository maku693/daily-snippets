cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(clang-tidy CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE
  "-Werror"
  "-Weverything"
  "-Wno-c++98-compat"
  "-Wno-c++98-compat-pedantic")
set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_CLANG_TIDY "clang-tidy;-checks=-*")
