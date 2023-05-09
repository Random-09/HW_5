cmake_minimum_required(VERSION 3.24)
project(task3 C)

set(CMAKE_C_STANDARD 11)

add_executable(task3 main.c source/merge_sort.c include/merge_sort.h source/database.c include/database.h source/file_parsing.c include/file_parsing.h sha-2/sha-256.c sha-2/sha-256.h)
