#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("%s <количество чисел>\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]);

    key_t key = ftok("numbers.txt", 65);
    if (key == -1) {
        perror("Ошибка создания ключа");
        return 1;
    }

    int semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("Ошибка создания семафора");
        return 1;
    }

    union semun arg;
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("Ошибка инициализации семафора");
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Ошибка создания процесса");
            return 1;
        } else if (pid == 0) {
            srand(time(NULL) ^ (getpid() << 16));
            int random_number = rand();

            struct sembuf sb = {0, -1, 0};
            semop(semid, &sb, 1);

            FILE *file = fopen("numbers.txt", "a");
            if (file != NULL) {
                fprintf(file, "%d\n", random_number);
                fclose(file);
            }

            sb.sem_op = 1;
            semop(semid, &sb, 1);

            exit(0);
        }
    }

    int status;
    while ((wait(&status) > 0)) {
        printf("Ожидание завершения всех дочерних процессов...\n");
    }

    if (semctl(semid, 0, IPC_RMID, arg) == -1) {
        perror("Ошибка уничтожения семафора");
        return 1;
    }

    return 0;
}
