#ifndef SOCKET_UTIL_SOCKET_UTIL_H
#define SOCKET_UTIL_SOCKET_UTIL_H

#include <bits/socket.h>

struct AddressIPv4Info {
    int domain;
    int type;
    int protocol;
};

int create_ipv4_socket();

struct sockaddr_in* configure_socket_address(char *ip, short port);

#endif //SOCKET_UTIL_SOCKET_UTIL_H
