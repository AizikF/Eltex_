#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("%s <количество чисел>\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]);
    int fd[2];
    pipe(fd);

    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Ошибка создания процесса");
            return 1;
        } else if (pid == 0) {
            close(fd[0]);
            srand(time(NULL) ^ (getpid() << 16));
            int random_number = rand();
            write(fd[1], &random_number, sizeof(random_number));
            close(fd[1]);
            exit(0);
        }
    }

    close(fd[1]);

    int status;
    while ((wait(&status) > 0)) {
        int random_number;
        read(fd[0], &random_number, sizeof(random_number));
        printf("Случайное число = %d\n", random_number);
    }

    close(fd[0]);

    return 0;
}
