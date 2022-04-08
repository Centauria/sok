set(src_dir ${CMAKE_SOURCE_DIR}/3rd-party/inih)

set(src_test INIReaderTest.cpp)
set(headers INIReader.h)

list(TRANSFORM src_test PREPEND ${src_dir}/)
list(TRANSFORM headers PREPEND ${src_dir}/)

add_library(inih INTERFACE)
target_include_directories(inih INTERFACE ${src_dir})

mark_as_advanced(${src_dir})