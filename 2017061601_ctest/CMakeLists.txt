cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

enable_testing()

project("20170615")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/main.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

add_executable("${PROJECT_NAME}_test" "${CMAKE_SOURCE_DIR}/test.cpp")
target_include_directories("${PROJECT_NAME}_test" PRIVATE ${CMAKE_SOURCE_DIR})
add_test("all" "${PROJECT_NAME}_test")
