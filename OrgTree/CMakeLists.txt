cmake_minimum_required(VERSION 3.4)
project(OrgTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp OrgTree.cpp OrgTree.h)
add_executable(OrgTree ${SOURCE_FILES})