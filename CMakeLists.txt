cmake_minimum_required(VERSION 3.25)

set(SPHINX_TARGET "posix" CACHE STRING "Build target")
set_property(CACHE SPHINX_TARGET PROPERTY STRINGS posix esp32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${SPHINX_TARGET})

file(GLOB SOURCES kernel/*.cpp fs/bifs/*.cpp)

if(SPHINX_TARGET STREQUAL "posix")
    add_executable(sphinx)
    target_include_directories(sphinx PRIVATE ${CMAKE_SOURCE_DIR})

    file(GLOB POSIX_SOURCES targets/posix/*.cpp)
    target_sources(sphinx PRIVATE ${SOURCES} ${POSIX_SOURCES})
elseif(SPHINX_TARGET STREQUAL "esp32")
    set(EXTRA_COMPONENT_DIRS targets/esp32)
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
else()
    message(FATAL_ERROR "Unknown target `${SPHINX_TARGET}`")
endif()

project(Sphinx LANGUAGES C CXX)

if(SPHINX_TARGET STREQUAL "esp32")
    set(COMPONENTS targets/esp32)
    idf_build_set_property(MINIMAL_BUILD ON)
endif()