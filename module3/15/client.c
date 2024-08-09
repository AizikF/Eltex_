#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int32_t socketClient;
    struct sockaddr_in serv_addr;

    char buffer[1024] = {0};
    char operation[10];
    double num1, num2;

    if ((socketClient = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Создание сокета завершилось неудачно");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7777); 

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nIP адрес некорректный\n");
        return -1;
    }

    if (connect(socketClient, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nОшибка присоеденения\n");
        return -1;
    }

    printf("Введите операцию (+, -, *, /): ");
    scanf("%s", operation);
    printf("Введите первое число: ");
    scanf("%lf", &num1);
    printf("Введите второе число: ");
    scanf("%lf", &num2);

    snprintf(buffer, sizeof(buffer), "%s %lf %lf", operation, num1, num2);
    send(socketClient, buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(socketClient, buffer, sizeof(buffer), 0);

    printf("Результат: %s\n", buffer);
    close(socketClient);

    return 0;
}
