#include <sys/socket.h>
#include <netinet/in.h>
#include "socket-util.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

//#define PORT 80
//#define IP "142.251.37.14"
#define PORT 3069
#define IP "127.0.0.1"

void send_http_req_to_google(int fd) {
    char* req = "GET / HTTP/1.1\r\nHost: google.com\r\n\r\n";
    int send_re = send(fd, req, strlen(req), 0);

    printf("bytes sent = %d\n", send_re);

    char buffer[1024] = {0};
    ssize_t recv_re = recv(fd, buffer, 1024, 0);

    printf("bytes received = %zd\n", recv_re);
    printf("payload = %s\n", buffer);
}

int main() {
    int client_fd = create_tcp_ipv4_socket();
    struct sockaddr_in *server_addr = create_ipv4_address(IP, PORT);
//    struct sockaddr_in addr;
//    addr.sin_port = htons(PORT);
//    addr.sin_family = AF_INET;
//    inet_pton(AF_INET, IP, &addr.sin_addr.s_addr);

    // 1. Client's file descriptor
    // 2. Servers socket address
    // 3. Servers socket address size
    int conn = connect(client_fd, (struct sockaddr *) server_addr, sizeof (*server_addr));

    if(conn == 0) {
        printf("Connected successfully.\n");
    }

//    send_http_req_to_google(client_fd);


//  =============================================
//    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
//    struct sockaddr_in addr;
//    addr.sin_port = htons(PORT);
//    addr.sin_family = AF_INET;
//    inet_pton(AF_INET, IP, &addr.sin_addr.s_addr);
//
//
//    int conn = connect(sock_fd, (struct sockaddr *) &addr, sizeof addr);

//    if(conn == 0) {
//        printf("conected successfully\n");
//    }
//  =============================================

    char message[1024];
    while(1) {
        printf("Enter message: ");
        if(fgets(message, 1024, stdin) == NULL) {
            printf("an error while reading from stdin.\n");
        }

        int idx = strcspn(message, "\n");
        message[idx] = '\0';

        if(strcmp(message, "exit") == 0) {
            break;
        }

        size_t len = strlen(message);

        send(client_fd, message, strlen(message), 0);
    }

    close(client_fd);

//    char buffer[1024] = {'b', 'y', 'e'};
//    while(1) {
//        printf("Enter text: ");
//        fgets(buffer, 1024, stdin);
//
//        // Replace newline with EOF
//        buffer[strcspn(buffer, "\n")] = '\0';
//
//        if(strcmp(buffer, "exit") == 0) {
//            printf("Exiting...");
//            break;
//        }
//
//        printf("Sending...\n");
//        send(client_fd, buffer, strlen(buffer), 0);
//        printf("Message sent.\n");
//    }
//
//    // Close connection
//    close(client_fd);
}
