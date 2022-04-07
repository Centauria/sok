cmake_minimum_required(VERSION 3.0.0)
project(sok VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/sdl2-cmake-modules/" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})

set(CMAKE_LIBRARY_ARCHITECTURE x64)
set(FIND_LIBRARY_USE_LIB64_PATHS TRUE)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_compile_definitions("_THREAD_SAFE")

find_package(SDL2 REQUIRED)

add_subdirectory(libSDL2pp)
find_package(SDL2PP REQUIRED)

find_package(inih REQUIRED)

add_executable(sok
    main.cpp
    src/engine.cpp
    src/gamemap.cpp
    src/util.cpp)
target_link_libraries(sok SDL2::Main SDL2pp inih)
target_include_directories(sok PUBLIC include)
target_include_directories(sok PUBLIC ${SDL2PP_INCLUDE_DIRS})
target_compile_definitions(sok PRIVATE LITE_ARRAY_NO_HINT NDEBUG)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/maps
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/maps)
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/config
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/config)
