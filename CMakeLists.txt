# stop if cmake version below 3.15
cmake_minimum_required(VERSION 3.15)

# project name
project(VendingMachine)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build/)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(VendingMachine ${SOURCES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/data)