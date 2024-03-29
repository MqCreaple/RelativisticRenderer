cmake_minimum_required(VERSION 3.16)

project(RelativisticRenderer VERSION 0.1)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_CXX_FLAGS "-march=native")
set(SDL2_DIR "ext/SDL2-2.28.5")

find_package(SDL2 REQUIRED)
find_package(Threads)

include_directories(${SDL2_INCLUDE_DIRS} include src)

include(CTest)

add_subdirectory(src)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(test)
endif()

enable_testing()