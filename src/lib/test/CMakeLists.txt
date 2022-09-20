cmake_minimum_required(VERSION 3.0.0)

project(Test CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_library(Test math.cpp)
target_include_directories (Test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})