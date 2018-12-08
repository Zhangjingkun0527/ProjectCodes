cmake_minimum_required(VERSION 3.12)
project(Algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(Algorithm main.cpp definitions.h random_number_generator.cpp
        insert_sort.cpp util.cpp quick_sort.cpp
        merge_sort.cpp heap_sort_using_ternary_tree.cpp)