cmake_minimum_required(VERSION 3.26)
project(socket_util C)

set(CMAKE_C_STANDARD 99)

add_library(socket_util socket-util.c)
