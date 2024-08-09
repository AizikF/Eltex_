#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7777 

void calculate(char *operation, double num1, double num2, char **result)
{
    *result = malloc(1024 * sizeof(char)); 
    memset(*result, 0, 1024);

    if (strcmp(operation, "+") == 0)
        sprintf(*result, "%f", num1 + num2);
    else if (strcmp(operation, "-") == 0)
        sprintf(*result, "%f", num1 - num2);
    else if (strcmp(operation, "*") == 0)
        sprintf(*result, "%f", num1 * num2);
    else if (strcmp(operation, "/") == 0)
    {
        if (num2 != 0)
            sprintf(*result, "%f", num1 / num2);
        else
            strcpy(*result, "Деление на ноль");
    }
    else
        strcpy(*result, "Ошибка: неизвестная операция");
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int32_t opt = 1;
    socklen_t addrlen = sizeof(address);

    char buffer[1024] = {0};
    char *result;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Создание сокета завершилось неудачно");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
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

    printf("Сервер слушает порт %d\n", PORT);

    while (1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0)
        {
            perror("accept failed");
            continue;
        }

        read(new_socket, buffer, 1024);
        printf("Получено: %s\n", buffer);

        char operation[10];
        double num1, num2;
        sscanf(buffer, "%s %lf %lf", operation, &num1, &num2);
        calculate(operation, num1, num2, &result);
        send(new_socket, result, strlen(result), 0);
        free(result);
        close(new_socket);
    }

    return 0;
}
