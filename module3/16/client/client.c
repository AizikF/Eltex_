#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>


#define PORT 7777
#define BUF_SIZE 1024

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};
    int32_t openFlags = O_CREAT|O_RDWR|O_APPEND;
    int32_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Сокет не может быть создан \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\n Неверный адрес \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\n Подключение не удалось \n");
        return -1;
    }

    const char *filename = "pypy.txt";
    send(sock, filename, strlen(filename), 0);

    int32_t outputFd = open(filename, openFlags, filePerms);
    if (outputFd == -1)
    {
        perror ("Ошибка открытия файла %s\n ");
        return -1;
    }

    size_t bytes_received;
    while ((bytes_received = recv(sock, buffer, BUF_SIZE, 0)) > 0)
    {
        write(outputFd, buffer, bytes_received);
    }

    printf("Файл получен успешно.\n");
    close(outputFd);
    close(sock);
    return 0;
}