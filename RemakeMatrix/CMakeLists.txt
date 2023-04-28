cmake_minimum_required(VERSION 3.25)
project(RemakeMatrix2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        RemakeMatrix2
        main.cpp
        rematrix.cpp
        rematrix.h
        auxiliary.h
        auxiliary.cpp
)
