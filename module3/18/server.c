#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>

#define PORT 9999
#define MAX_CLIENTS 10

void calculate(char *operation, double num1, double num2, char *result)
{
    if (strcmp(operation, "+") == 0)
        sprintf(result, "%f", num1 + num2);
    else if (strcmp(operation, "-") == 0)
        sprintf(result, "%f", num1 - num2);
    else if (strcmp(operation, "*") == 0)
        sprintf(result, "%f", num1 * num2);
    else if (strcmp(operation, "/") == 0)
    {
        if (num2 != 0)
            sprintf(result, "%f", num1 / num2);
        else
            strcpy(result, "Деление на ноль");
    }
    else
        strcpy(result, "Error: Unknown operation");
}
int main()
{
    int server_fd, new_socket, max_sd;
    struct sockaddr_in address;
    int32_t opt = 1;
    int32_t addrlen = sizeof(address);
    fd_set readfds;

    char buffer[1024] = {0};
    char result[1024] = {0};

    // Массив сокетов для обработки нескольких клиентов
    int client_sockets[MAX_CLIENTS] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Создание сокета завершилось неудачно");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Ошибка привязки сокета");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Сервер слушает порт 9999\n");
    while (1)
    {
        // Сбросить множественный набор
        FD_ZERO(&readfds);

        // Добавить серверный сокет в набор
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        // Добавить клиентские сокеты
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            int sd = client_sockets[i];
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max_sd)
                max_sd = sd;
        }

        // Ожидание активности в сетевых сокетах
        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            perror("select error");
        }

        // Если есть входящее соединение на серверный сокет
        if (FD_ISSET(server_fd, &readfds))
        {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
            {
                perror("accept failed");
                continue;
            }

            printf("Новое соединение: socket fd %d, ip %s, port %d\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            // Добавить новый сокет в массив клиентских сокетов
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = new_socket;
                    printf("Добавили сокет в индекс %d\n", i);
                    break;
                }
            }
        }

        // Обработка входящих сообщений от всех клиентов
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            int sd = client_sockets[i];
            if (FD_ISSET(sd, &readfds))
            {
                int valread = read(sd, buffer, 1024);
                if (valread == 0)
                {
                    // Клиент отключился, закрываем сокет
                    getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                    printf("Клиент отключился: socket fd %d, ip %s, port %d\n", sd, inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    close(sd);
                    client_sockets[i] = 0; // Удаляем сокет из массива
                }
                else
                {
                    // Обрабатываем входящее сообщение
                    buffer[valread] = '\0'; // Завершаем строку
                    printf("Получено от клиента (socket fd %d): %s\n", sd, buffer);

                    char operation[10];
                    double num1, num2;
                    sscanf(buffer, "%s %lf %lf", operation, &num1, &num2);
                    calculate(operation, num1, num2, result);
                    send(sd, result, strlen(result), 0);
                }
            }
        }
    }

    return 0;
}