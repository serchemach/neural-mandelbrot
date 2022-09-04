cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MandelbrotC)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES src/main.c src/lodepng.c src/image_encode.c src/mandelbrot.c src/neural_network_stuff.c
            src/genann.c)
add_executable(MandelbrotC ${SOURCES})
include_directories(MandelbrotC include)
SET(CMAKE_EXE_LINKER_FLAGS  "-static-libgcc -static-libstdc++ -ansi -pedantic -Wall -Wextra -O3")


