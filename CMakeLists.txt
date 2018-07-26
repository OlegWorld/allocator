cmake_minimum_required(VERSION 3.10)
project(allocator)

set(CMAKE_CXX_STANDARD 14)

add_executable(allocator main.cpp allocator.h)