cmake_minimum_required(VERSION 3.20)
project(example_proj C)

set(CMAKE_C_STANDARD 99)

add_executable(example_proj dyn_mem_alloc_examples.c dyn_mem_alloc_2d_arr.c code_practice_1.c scratch_pad_11-05-2021.c scratch_pad_11-12-21.c scratch_pad_11-27-21.c)
