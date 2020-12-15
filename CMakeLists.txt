
cmake_minimum_required(VERSION 3.16)
project(chest)

find_library(libfltk libfltk.a)
find_library(libfltk_images libfltk_images.a)
find_library(libsodium libsodium.a)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD 14)

add_executable(chest
        main.c
        enc.c
        cmd.c
        gui/gui.cpp)

target_link_libraries(chest sodium fltk fltk_images)