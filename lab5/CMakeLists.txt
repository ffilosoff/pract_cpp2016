cmake_minimum_required(VERSION 3.4)
project(lab5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    libtap-master/tap.c
    libtap-master/tap.h
    main.cpp)
#libtap/tap.c
#libtap/tap.h
#libtap/vs_patch_tap.c
#libtap/vs_patch_tap.h
#libtap/vs_tap.h
add_executable(lab5 ${SOURCE_FILES})