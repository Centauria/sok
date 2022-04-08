cmake_minimum_required(VERSION 3.0.0)
project(sok VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(CMAKE_LIBRARY_ARCHITECTURE x64)
set(FIND_LIBRARY_USE_LIB64_PATHS TRUE)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/3rd-party/sdl2-cmake-modules/")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/")

find_package(SDL2 REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/3rd-party/libSDL2pp)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rd-party/argparse)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rd-party/blobify)

add_subdirectory(sok)
add_subdirectory(pack)
