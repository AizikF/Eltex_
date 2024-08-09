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

    sem_t sem_write, sem_read;

    if (sem_init(&sem_write, 1, 1) == -1 || sem_init(&sem_read, 1, 1) == -1) {
        perror("Ошибка инициализации семафоров");
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

            sem_wait(&sem_read);
            sem_wait(&sem_write);

            FILE *file = fopen("numbers.txt", "a");
            if (file != NULL) {
                fprintf(file, "%d\n", random_number);
                fclose(file);
            }

            sem_post(&sem_write);
            sem_post(&sem_read);

            exit(0);
        }
    }

    int status;
    while ((wait(&status) > 0)) {
        printf("\nОжидание завершения всех дочерних процессов...\n");
    }

    sem_destroy(&sem_write);
    sem_destroy(&sem_read);

    return 0;
}
