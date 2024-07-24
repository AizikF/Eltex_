#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void endProgram() {
    printf("Завершение работы программы\n");
}

int main(int32_t argc, char* argv[]) {
    atexit(endProgram);

    pid_t childPid = fork();

    if (childPid == -1) {
        perror("Ошибка при создании дочернего процесса");
        exit(EXIT_FAILURE);
    } else if(childPid == 0) {
        printf("Площадь квадратов посчитанная в дочернем процессе\n");
        for (int32_t i = 2; i < argc; i += 2) {
            printf("Площадь квадрата со стороной %d = %d\n", atoi(argv[i]), atoi(argv[i]) * atoi(argv[i]));
        }
    } else {
        printf("Площадь квадратов посчитанная в родителе\n");
        for (int32_t i = 1; i < argc; i += 2) {
            printf("Площадь квадрата со стороной %d = %d\n", atoi(argv[i]), atoi(argv[i]) * atoi(argv[i]));
        }
        int status;
        waitpid(childPid, &status, 0);
    }

    return EXIT_SUCCESS;
}
