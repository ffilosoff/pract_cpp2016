cmake_minimum_required(VERSION 3.3)
project(lab3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    1729.cpp)

add_executable(lab3 ${SOURCE_FILES})