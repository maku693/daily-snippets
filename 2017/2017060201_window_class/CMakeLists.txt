cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project("2017060201")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(
  -DUNICODE -D_UNICODE
  )

add_executable(${PROJECT_NAME} WIN32 main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )
