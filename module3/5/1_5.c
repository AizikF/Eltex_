#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

void child_signal_handler(int sig) {
    static int access_blocked = 0;

    if (sig == SIGUSR1) {
        access_blocked = 1;
    } else if (sig == SIGUSR2) {
        access_blocked = 0;
    }
}

void parent_signal_handler(int sig) {
    if (sig == SIGUSR2) {
        printf("Дочерний процесс завершил запись числа.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("%s <количество чисел>\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]);
    int fd[2];
    pipe(fd);

    signal(SIGUSR1, child_signal_handler);
    signal(SIGUSR2, parent_signal_handler);

    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Ошибка создания процесса");
            return 1;
        } else if (pid == 0) {
            close(fd[0]);
            srand(time(NULL) ^ (getpid() << 16));
            int random_number = rand();

            kill(getppid(), SIGUSR1);

            FILE *file = fopen("numbers.txt", "a");
            if (file != NULL) {
                fprintf(file, "%d\n", random_number);
                fclose(file);
            }

            kill(getppid(), SIGUSR2);

            exit(0);
        }
    }

    close(fd[1]);

    int status;
    while ((wait(&status) > 0)) {
        printf("Ожидание завершения всех дочерних процессов...\n");
    }

    close(fd[0]);

    return 0;
}
