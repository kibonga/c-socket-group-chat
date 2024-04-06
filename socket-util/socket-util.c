#include "socket-util.h"
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

void hello_foo_lib(void) {
    printf("Hello, World from foo lib!\n");
}

int create_ipv4_socket() {
    int file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if(file_descriptor == -1) {
        perror("Failed to create socket.\n");
        exit(EXIT_FAILURE);
    }

    return file_descriptor;
}

struct sockaddr_in* configure_socket_address(char *ip, short port) {
    struct sockaddr_in *addr = malloc(sizeof (struct sockaddr_in));
    addr->sin_port = htons(port);
    addr->sin_family = AF_INET;
    memset(addr->sin_zero, 0, sizeof addr->sin_zero);

    // Convert text to IPv4 and bind to socket address
    if(strlen(ip) == 0) {
        addr->sin_addr.s_addr = INADDR_ANY;
    }else {
        inet_pton(AF_INET, ip, &addr->sin_addr.s_addr);
    }

    return addr;
}
