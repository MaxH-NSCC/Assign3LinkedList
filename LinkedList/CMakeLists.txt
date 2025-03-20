cmake_minimum_required(VERSION 3.29)
project(LinkedLists C)

set(CMAKE_C_STANDARD 11)

add_executable(LinkedLists main.c
        linked_list.c
        linked_list.h
)
