#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>


#define PORT 7777
#define BUF_SIZE 1024

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Сервер запущен. Ожидание соединения...\n");

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, BUF_SIZE);
    printf("Получен запрос на файл: %s\n", buffer);

    int32_t inputFd = open("glock.png", O_RDONLY);
    if (inputFd == -1)
    {
        perror ("Ошибка чтения");
        return -1;
    }

    int32_t nBytes;
    while((nBytes = read(inputFd, buffer, sizeof(buffer))) > 0)
    {
        send(new_socket, buffer, nBytes, 0);
    }

    printf("Файл передан успешно.\n");
    close(inputFd);
    close(new_socket);
    close(server_fd);

    return 0;
}