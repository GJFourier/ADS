cmake_minimum_required(VERSION 3.24)
project(lab0_stu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab0_stu
        main.cpp
        SparseMatrix.cpp
        SparseMatrix.h)
