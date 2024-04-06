#include <sys/socket.h>
#include <netinet/in.h>
#include "socket-util.h"
#include <stdio.h>
#include <stdlib.h>

#define PORT 3069
#define IP "127.0.0.1"

int main() {
    int server_fd = create_ipv4_socket();
    struct sockaddr_in *server_sock_addr = configure_socket_address(IP, PORT);

    socklen_t server_sock_size = sizeof (*server_sock_addr);
    int conn = connect(server_fd, (struct sockaddr *) server_sock_addr, server_sock_size);

    if(conn == -1) {
        perror("Failed to connect.\n");
        exit(EXIT_FAILURE);
    }


}
