cmake_minimum_required(VERSION 3.20)
project(example_proj C)

set(CMAKE_C_STANDARD 99)

add_executable(example_proj dyn_mem_alloc_examples.c dyn_mem_alloc_2d_arr.c)
