cmake_minimum_required(VERSION 3.7)

project(Mandelbrot)

add_executable(Mandelbrot src/main.cpp src/functions.cpp src/plot.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_path(FREEIMAGE_INCLUDE_DIR FreeImage.h)
include_directories(${FREEIMAGE_INCLUDE_DIR})

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

target_link_libraries(Mandelbrot freeimage)