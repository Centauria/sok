cmake_minimum_required(VERSION 3.0.0)
project(pack VERSION 0.1.0)

add_executable(pack src/pack-main.cpp src/pack.cpp)
target_link_libraries(pack argparse util)
target_include_directories(pack PUBLIC include)

add_library(pack-lib src/pack.cpp)
target_link_libraries(pack-lib util)
target_include_directories(pack-lib PUBLIC include)

add_library(pack::lib ALIAS pack-lib)
