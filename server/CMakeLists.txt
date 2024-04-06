cmake_minimum_required(VERSION 3.26)
project(server C)

set(CMAKE_C_STANDARD 99)

find_path(SocketUtilLibHeader socket-util.h
        PATHS /home/pdjurdjic/repos/c-socket-group-chat/socket-util)

find_library(SocketUtilLib
        NAMES socket_util
        PATHS /home/pdjurdjic/repos/c-socket-group-chat/socket-util/cmake-build-debug
)

add_executable(server main.c)
target_include_directories(server PRIVATE ${SocketUtilLibHeader})
target_link_libraries(server ${SocketUtilLib})
