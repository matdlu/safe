cmake_minimum_required(VERSION 3.14)
project(chest)

include(FetchContent)

set(build_type "static")

if ( build_type STREQUAL "static" )
    # static build
    # will download and build libraries locally
    FetchContent_Declare(
            libsodium
            URL "https://download.libsodium.org/libsodium/releases/libsodium-1.0.18-stable.tar.gz"
            URL_HASH MD5=344a6c1c28315de9f20d86a8b2f13390
    )

    FetchContent_Declare(
            libfltk
            URL "https://www.fltk.org/pub/fltk/1.3.5/fltk-1.3.5-source.tar.gz"
            URL_HASH MD5=e85017defd5a03ae82e634311db87bbf
    )

    FetchContent_MakeAvailable(libsodium libfltk)
else()
    # dynamic build
    # will use system libraries
    find_library(libfltk libfltk.a)
    find_library(libfltk_images libfltk_images.a)
    find_library(libsodium libsodium.a)
endif()

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD 14)

add_executable(chest
        main.c
        enc.c
        cmd.c
        gui/gui.cpp)

target_link_libraries(chest sodium fltk fltk_images)