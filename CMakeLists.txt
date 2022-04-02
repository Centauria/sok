cmake_minimum_required(VERSION 3.0.0)
project(sok VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/sdl2-cmake-modules/" ${CMAKE_MODULE_PATH})

if (UNIX)
    add_compile_definitions(UNIX)
endif ()

if (APPLE)
    add_compile_definitions(APPLE)
endif ()

if (WIN32)
    add_compile_definitions(WIN32)
endif ()

find_package(SDL2 REQUIRED)

add_executable(sok 
    main.cpp 
    src/engine.cpp 
    src/gamemap.cpp 
    src/util.cpp)
target_link_libraries(sok SDL2::Main)
target_include_directories(sok PUBLIC include)
target_compile_definitions(sok PRIVATE LITE_ARRAY_NO_HINT NDEBUG)
