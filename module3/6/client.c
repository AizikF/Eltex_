#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080

void send_ping(int sock) {
    char buffer[1024] = {0};
    strcpy(buffer, "Ping");
    printf("Sending 'Ping' to server...\n");
    send(sock, buffer, strlen(buffer), 0);
}

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &(server_addr.sin_addr));

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    while (1) {
        send_ping(sock); // Отправляем "Ping"

        recv(sock, buffer, 1024, 0);
        printf("Received from server: %s\n", buffer);

        sleep(1);
    }

    close(sock);
    return 0;
}
