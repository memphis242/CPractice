cmake_minimum_required(VERSION 3.20)
project(rx_queue_hash C)

set(CMAKE_C_STANDARD 99)

add_executable(rx_queue_hash main.c std_can_ds.h std_can_ds.c callbacks.c)
