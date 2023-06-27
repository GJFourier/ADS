cmake_minimum_required(VERSION 3.24)
project(hw5)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw5 main.cpp rbtree.h avl_tree.h skiplist.h skiplist.cpp)
