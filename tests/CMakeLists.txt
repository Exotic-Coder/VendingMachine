# stop if cmake version below 3.15
cmake_minimum_required(VERSION 3.15)

# project name
project(testing)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build/)

include_directories(include)

file(GLOB SOURCES "*.cpp")

add_executable(testing ${SOURCES})