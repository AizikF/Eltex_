#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

#define SHM_KEY 12345

void generate_random_numbers(int shmid) {
    int* shared_memory = (int*)shmat(shmid, NULL, 0);
    if (shared_memory == (void*)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        shared_memory[i] = rand();
    }
}

void find_max_min_and_print_all(int shmid) {
    int* shared_memory = (int*)shmat(shmid, NULL, 0);
    if (shared_memory == (void*)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Генерация чисел:\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", shared_memory[i]);
    }
    printf("\n");

    int max = shared_memory[0];
    int min = shared_memory[0];

    for (int i = 1; i < 10; ++i) {
        if (shared_memory[i] > max) {
            max = shared_memory[i];
        }
        if (shared_memory[i] < min) {
            min = shared_memory[i];
        }
    }

    printf("Максимум: %d\n", max);
    printf("Минимум: %d\n", min);

    shared_memory[0] = max;
    shared_memory[1] = min;
}

void handle_sigint(int sig) {
    printf("\nReceived SIGINT. Exiting...\n");
    exit(EXIT_SUCCESS);
}

int main() {
    signal(SIGINT, handle_sigint);

    int shmid = shmget(SHM_KEY, sizeof(int) * 12, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        find_max_min_and_print_all(shmid);
    } else {
        generate_random_numbers(shmid);
        wait(NULL);
    }

    return 0;
}
