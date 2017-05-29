cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project("daily-snippets")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

file (GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

foreach(SOURCE ${SOURCES})
  get_filename_component(BIN_NAME ${SOURCE} NAME_WE)
  add_executable(${BIN_NAME} ${SOURCE})
endforeach()
