#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>

// Объявления функций обработчиков сигналов
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
        printf("Использование: %s <количество чисел>\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]);
    int fd[2];
    pipe(fd);

    sem_t *read_sema = sem_open("/read_sema", O_CREAT, 0644, 1);
    sem_t *write_sema = sem_open("/write_sema", O_CREAT, 0644, 1);
    if (!read_sema || !write_sema) {
        perror("Ошибка создания семафоров");
        return 1;
    }

    signal(SIGUSR1, child_signal_handler);
    signal(SIGUSR2, parent_signal_handler);

    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Ошибка создания процесса");
            return 1;
        } else if (pid == 0) { // Дочерний процесс
            close(fd[0]);
            srand(time(NULL) ^ (getpid() << 16));
            int random_number = rand();

            sem_wait(read_sema); // Ждем, пока никто не будет читать
            sem_wait(write_sema); // Захватываем семафор записи
            FILE *file = fopen("numbers.txt", "a");
            if (file != NULL) {
                fprintf(file, "%d\n", random_number);
                fclose(file);
            }
            sem_post(write_sema); // Освобождаем семафор записи
            sem_post(read_sema); // Повышаем счетчик чтения

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
    sem_close(read_sema);
    sem_close(write_sema);
    sem_unlink("/read_sema");
    sem_unlink("/write_sema");

    return 0;
}
