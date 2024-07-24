#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <количество чисел>\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]); // Количество чисел для генерации
    int fd[2]; // Массив для хранения двух концов канала
    pipe(fd); // Создание канала

    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Ошибка создания процесса");
            return 1;
        } else if (pid == 0) { // Дочерний процесс
            close(fd[0]); // Закрытие конца канала для чтения в дочернем процессе
            srand(time(NULL) ^ (getpid() << 16)); // Инициализация генератора случайных чисел
            int random_number = rand();
            write(fd[1], &random_number, sizeof(random_number)); // Отправка числа через канал
            close(fd[1]); // Закрытие конца канала для записи после отправки данных
            exit(0);
        }
    }

    close(fd[1]); // Закрытие конца канала для записи в родительском процессе

    int status;
    while ((wait(&status) > 0)) { // Ожидание завершения всех дочерних процессов
        int random_number;
        read(fd[0], &random_number, sizeof(random_number)); // Чтение числа из канала
        printf("Случайное число = %d\n", random_number);
    }

    close(fd[0]); // Закрытие конца канала для чтения

    return 0;
}
