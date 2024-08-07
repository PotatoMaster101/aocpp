cmake_minimum_required(VERSION 3.28)
project(aocpp)

set(CMAKE_CXX_STANDARD 23)

add_library(aocpp INTERFACE include)
target_include_directories(aocpp INTERFACE include)

enable_testing()
add_subdirectory(tests)
