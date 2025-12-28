cmake_minimum_required(VERSION 3.25)
project(Sphinx LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

add_executable(sphinx)

target_include_directories(sphinx PRIVATE ${CMAKE_SOURCE_DIR})

file(GLOB SOURCES kernel/*.cpp)
target_sources(sphinx PRIVATE ${SOURCES})

add_subdirectory(targets/posix)
add_subdirectory(fs/bifs)