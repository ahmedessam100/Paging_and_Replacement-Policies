cmake_minimum_required(VERSION 3.12)
project(Paging_and_Replacement C)

set(CMAKE_C_STANDARD 99)

add_executable(Paging_and_Replacement main.c Policy.h Policy.c)