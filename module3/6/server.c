#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define KEY 1234

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void init_semaphore(int sem_id) {
    union semun sem_union;
    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }
}

void destroy_semaphore(int sem_id) {
    union semun sem_union;
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }
}

void handle_client(int client_sock, int sem_id) {
    char buffer[1024] = {0};
    int read_size;

    while ((read_size = recv(client_sock, buffer, 1024, 0)) > 0) {
        struct sembuf sb[] = {{0, -1}, {0, 1}};
        if (semop(sem_id, sb, 2) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }
        printf("Received from client: %.*s\n", read_size, buffer);
        send(client_sock, "Pong", 4, 0);
    }

    close(client_sock);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    int sem_id = semget(KEY, 1, 0666 | IPC_CREAT);

    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    init_semaphore(sem_id);

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

        handle_client(client_sock, sem_id);
    }

    close(server_sock);
    destroy_semaphore(sem_id);
    return 0;
}
