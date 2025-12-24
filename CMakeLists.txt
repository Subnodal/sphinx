cmake_minimum_required(VERSION 3.25)
project(Sphinx LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/kernel/*.cpp
    targets/posix/*.cpp
)

add_executable(sphinx ${SOURCES})