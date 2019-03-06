cmake_minimum_required(VERSION 3.13)
project(lab_01)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_01
        data.txt
        error.h
        func.cpp
        func.h
        interpol.cpp
        interpol.h
        main.cpp
        makefile
        matrix.cpp
        matrix.h)
