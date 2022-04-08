cmake_minimum_required(VERSION 3.0.0)
project(sok-main VERSION 0.1.0)

add_compile_definitions("_THREAD_SAFE")

find_package(inih REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/engine.cpp
    src/gamemap.cpp
    ../util/util.cpp)
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2pp inih util)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2PP_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE LITE_ARRAY_NO_HINT NDEBUG)

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
