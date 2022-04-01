cmake_minimum_required(VERSION 3.0.0)
project(sok VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "sdl2-cmake-modules" ${CMAKE_MODULE_PATH})

find_package(SDL2 REQUIRED)

add_executable(sok 
    main.cpp 
    src/engine.cpp 
    src/gamemap.cpp 
    src/util.cpp)
target_link_libraries(sok SDL2)
target_include_directories(sok PUBLIC include)
target_compile_definitions(sok PRIVATE LITE_ARRAY_NO_HINT NDEBUG)
