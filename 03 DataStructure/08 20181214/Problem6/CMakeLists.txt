cmake_minimum_required(VERSION 3.13)
project(Problem6)

set(CMAKE_CXX_STANDARD 14)

add_executable(Problem6 main.cpp definitions.h question_1.cpp question_2.cpp question_3.cpp question_4.cpp
        random_number_generator.cpp binary_search.cpp util.cpp)