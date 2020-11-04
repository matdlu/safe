cmake_minimum_required(VERSION 3.16)
project(chest)

include_directories("C:/dependencies/libsodium-win64/include")
link_directories("C:/dependencies/libsodium-win64/lib")

include_directories("C:/msys64/mingw64/include")
link_directories("C:/msys64/mingw64/lib")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 90)

add_executable(chest main.c msd_str.h enc.h cmd.c gui.cpp gui.h cmd.h msd_uca.h enc.c gui.hpp msd_rnd.h msd_io.h msd_dyn.h msd_type.h)

target_link_libraries(chest mingw32 libsodium libfltk libfltk_images)
