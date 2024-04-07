#ifndef SOCKET_UTIL_SOCKET_UTIL_H
#define SOCKET_UTIL_SOCKET_UTIL_H

struct AddressIPv4Info {
    int domain;
    int type;
    int protocol;
};

int create_tcp_ipv4_socket();

struct sockaddr_in* create_ipv4_address(char *ip, short port);

#endif //SOCKET_UTIL_SOCKET_UTIL_H
