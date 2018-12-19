cmake_minimum_required(VERSION 3.13)
project(Problem5)

set(CMAKE_CXX_STANDARD 14)

add_executable(Problem5 main.cpp definitions.h random_number_generator.cpp sequential_search.cpp binary_search.cpp)