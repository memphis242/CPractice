cmake_minimum_required(VERSION 3.20)
project(general_sketchpad C)

set(CMAKE_C_STANDARD 99)

add_executable(general_sketchpad main.c circular_queue.c circular_queue.h)
