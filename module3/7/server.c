#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* handle_client(void* arg) {
    int client_sock = *(int*)arg;
    char buffer[1024] = {0};
    int read_size;

    while ((read_size = recv(client_sock, buffer, 1024, 0)) > 0) {
        pthread_mutex_lock(&mutex);
        printf("Received from client: %.*s\n", read_size, buffer);
        send(client_sock, "Pong", 4, 0);
        pthread_mutex_unlock(&mutex);
    }

    close(client_sock);
    return NULL;
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(server_sock, 3);

    printf("Waiting for incoming connections...\n");

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, handle_client, (void*)&client_sock);
    }

    close(server_sock);
    return 0;
}
