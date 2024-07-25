#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <semaphore.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("%s <количество чисел>\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]);
    int fd[2];
    pipe(fd);

    sem_t semaphore;
    if (sem_init(&semaphore, 1, 1) == -1) {
        perror("Ошибка инициализации семафора");
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Ошибка создания процесса");
            return 1;
        } else if (pid == 0) {
            close(fd[0]);
            srand(time(NULL) ^ (getpid() << 16));
            int random_number = rand();

            sem_wait(&semaphore);

            FILE *file = fopen("numbers.txt", "a");
            if (file != NULL) {
                fprintf(file, "%d\n", random_number);
                fclose(file);
            }

            sem_post(&semaphore);

            exit(0);
        }
    }

    close(fd[1]);

    int status;
    while ((wait(&status) > 0)) {
        printf("Ожидание завершения всех дочерних процессов...\n");
    }

    close(fd[0]);

    sem_destroy(&semaphore);

    return 0;
}
