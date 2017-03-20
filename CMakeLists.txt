cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

project(Snake)
set (SNAKE_VERSION_MAJOR 1)
set (SNAKE_VERSION_MINOR 0)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR}/src)
set (SNAKE_DATA_DIR "${CMAKE_BINARY_DIR}/src/data")
# TODO: move getDataDir to seperate .h.in file

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Please create an out-of-source build.")
endif()

option(SNAKE_BUILD_TESTS "Build tetris unit tests." OFF)

enable_testing()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
endif()

configure_file (
  "${PROJECT_SOURCE_DIR}/SnakeConfig.h.in"
  "${PROJECT_BINARY_DIR}/SnakeConfig.h"
)
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(libs)
