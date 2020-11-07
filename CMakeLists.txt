cmake_minimum_required(VERSION 3.16)
project(chest)

find_library(libfltk libfltk.a)
find_library(libfltk_images libfltk_images.a)
find_library(libsodium libsodium.a)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 90)

add_executable(chest main.c msd_str.h enc.h cmd.c gui.cpp gui.h cmd.h enc.c gui.hpp msd_io.h msd_type.h)

target_link_libraries(chest sodium fltk fltk_images)
