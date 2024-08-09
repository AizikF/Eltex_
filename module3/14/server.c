#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT_NUM 8080 
#define MAX_BUFFER_SIZE 1024 
int main()
{
    int serverSocket;
    struct sockaddr_in serverInfo, clientInfo[2]; 
    char receiveBuffer[MAX_BUFFER_SIZE];
    socklen_t addressLength = sizeof(clientInfo[0]);
    int connectedClients = 0;

    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }

    memset(&serverInfo, 0, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(PORT_NUM);

    if (bind(serverSocket, (const struct sockaddr *)&serverInfo, sizeof(serverInfo)) < 0)
    {
        perror("Ошибка привязки сокета");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Сервер запущен и ожидает сообщения...\n");
    char tempBuffer[MAX_BUFFER_SIZE];
    int recvSize, sendSize;
    while (1)
    {
        recvSize = recvfrom(serverSocket, (char *)tempBuffer, MAX_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&clientInfo[0], &addressLength);
        tempBuffer[recvSize] = '\0';
        sendSize = recvfrom(serverSocket, (char *)receiveBuffer, MAX_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&clientInfo[1], &addressLength);
        receiveBuffer[sendSize] = '\0';
        printf("%d %d\n", ntohs(clientInfo[0].sin_port), ntohs(clientInfo[1].sin_port));
        sendto(serverSocket, tempBuffer, recvSize, MSG_CONFIRM, (const struct sockaddr *)&clientInfo[1], addressLength);
        sendto(serverSocket, receiveBuffer, sendSize, MSG_CONFIRM, (const struct sockaddr *)&clientInfo[0], addressLength);
    }

    close(serverSocket);
    return 0;
}
