cmake_minimum_required(VERSION 3.3)
project(CPP_Playground)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    LargestWordRectangleFinder.cpp
    LargestWordRectangleFinder.hpp)

add_executable(CPP_Playground ${SOURCE_FILES})