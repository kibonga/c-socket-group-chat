#include <stdio.h>
#include "socket-util.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#define IP "127.0.0.1"
#define PORT 3069
#define NUM_OF_CONN 5

struct AcceptedClientSocket {
    int client_fd;
    struct sockaddr_in address;
    bool error;
};

struct AcceptedClientSocket *accept_client_connection(int server_fd);

void receive_and_print_client_data(int client_fd);

void start_accepting_connections(int server_fd);

void start_client_connection_on_new_thread(int client_fd);

void *start_client_connection(void *client_fd);

// Accepts servers file descriptor and accepts the client connection
// Returns AcceptedClientSocket with client connection information
struct AcceptedClientSocket *accept_client_connection(int server_fd) {
    struct sockaddr_in client_addr;
    socklen_t client_sock_len = sizeof client_addr;

    printf("Accepting client connection...\n");
    int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_sock_len);

    size_t client_sock_size = sizeof(struct AcceptedClientSocket);
    struct AcceptedClientSocket *client_sock = malloc(client_sock_size);

    client_sock->client_fd = client_fd;
    client_sock->address = client_addr;
    client_sock->error = client_fd < 0;

    if(client_sock->error) {
        printf("Failed to connect.\n");
    }else {
        printf("Successfully connected.\n");
    }

    return client_sock;
}

// Accepts clients file descriptor and starts receiving clients data and finally prints it
// Data is stored in buffer and on each receive is printed out
void receive_and_print_client_data(int client_fd) {
    char buffer[1024];
    size_t bytes_read;

    while (1) {
        bytes_read = recv(client_fd, buffer, 1024, 0);

        // No bytes received
        if (bytes_read == 0) {
            break;
        }

        // This is needed to set the EOF in buffer because of the previous values that were in the buffer
        // We could potentially use memset to 0
        buffer[bytes_read] = 0;

        printf("message = %s\n", buffer);
    }
}

void start_accepting_connections(int server_fd) {

    while (1) {
        struct AcceptedClientSocket *client_sock = accept_client_connection(server_fd);

        if (client_sock->error) {
            printf("failed to make connection with client");
            break;
        }

        start_client_connection_on_new_thread(client_sock->client_fd);
    }

}

void start_client_connection_on_new_thread(int client_fd) {
    pthread_t id;
    pthread_create(&id, NULL, start_client_connection, &client_fd);
}

void *start_client_connection(void *client_fd) {
    int fd = *(int *) client_fd;
    receive_and_print_client_data(fd);
    close(fd);

    return NULL;
}

int main() {
    // CREATE A SOCKET
    int server_fd = create_tcp_ipv4_socket();

    // CREATE SOCKET SERVER ADDRESS
    struct sockaddr_in *server_addr = create_ipv4_address(IP, PORT);

    // ASSIGN SOCKET NAME
    if (bind(server_fd, (struct sockaddr *) server_addr, sizeof(*server_addr)) == -1) {
        perror("failed to bind.\n");
        exit(EXIT_FAILURE);
    }

    // OPEN SOCKET
    listen(server_fd, NUM_OF_CONN);

    // START ACCEPTING CONNECTION ON SEPARATE THREADS (blocking call)
    start_accepting_connections(server_fd);

    shutdown(server_fd, SHUT_RDWR);
}
