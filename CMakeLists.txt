cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        distance_calculator.c
        distance_calculator.h
        explicit_data.c
        explicit_data.h
        node.h
)
