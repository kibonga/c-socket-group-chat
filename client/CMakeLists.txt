cmake_minimum_required(VERSION 3.26)
project(client C)

set(CMAKE_C_STANDARD 99)

find_path(SocketUtilLibHeader socket-util.h
    PATHS /home/pdjurdjic/repos/c-socket-group-chat/socket-util
)

find_library(SocketUtilLib
    NAMES socket_util
    PATHS /home/pdjurdjic/repos/c-socket-group-chat/socket-util/cmake-build-debug
)

add_executable(client main.c)
target_include_directories(client PRIVATE ${SocketUtilLibHeader})
target_link_libraries(client ${SocketUtilLib})
