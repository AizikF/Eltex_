#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT_NUM 8080 
#define SERVER_IP_ADDRESS "127.0.0.1" 
#define MAX_BUFFER_SIZE 1024

int main()
{
    int clientSocket;
    struct sockaddr_in serverDetails;
    char messageBuffer[MAX_BUFFER_SIZE];

    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }

    memset(&serverDetails, 0, sizeof(serverDetails));
    serverDetails.sin_family = AF_INET;
    serverDetails.sin_port = htons(PORT_NUM);
    inet_pton(AF_INET, SERVER_IP_ADDRESS, &serverDetails.sin_addr);

    while (1)
    {
        printf("Введите сообщение: ");
        fgets(messageBuffer, MAX_BUFFER_SIZE, stdin);

        sendto(clientSocket, messageBuffer, strlen(messageBuffer), MSG_CONFIRM, (const struct sockaddr *)&serverDetails, sizeof(serverDetails));

        int n = recvfrom(clientSocket, (char *)messageBuffer, MAX_BUFFER_SIZE, MSG_WAITALL, NULL, NULL);
        messageBuffer[n] = '\0';
        printf("Ответ от сервера: %s\n", messageBuffer);
    }

    close(clientSocket);
    return 0;
}
