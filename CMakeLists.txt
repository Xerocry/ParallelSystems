cmake_minimum_required(VERSION 3.6)
project(Parallel)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Single.c my_random.h)
add_executable(Parallel ${SOURCE_FILES})