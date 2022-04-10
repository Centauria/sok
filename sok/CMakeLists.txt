cmake_minimum_required(VERSION 3.0.0)
project(sok-main VERSION 0.1.0)

add_compile_definitions("_THREAD_SAFE")

find_package(inih REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/engine.cpp
    src/gamemap.cpp
    src/load.cpp
    src/data.cpp)
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2pp inih util lunasvg pack::lib)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2PP_INCLUDE_DIRS})

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
