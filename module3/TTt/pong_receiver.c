#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 1024
#define MSG_KEY 1234 // Используем тот же ключ, что и у отправителя

struct msg_buffer {
    long message_type;
    char text[MSG_SIZE];
};

int main() {
    struct msg_buffer receive_msg;
    int msgid;

    // Получаем дескриптор очереди сообщений
    msgid = msgget(MSG_KEY, 0666);

    while (1) { // Бесконечный цикл для постоянного прослушивания
        msgrcv(msgid, &receive_msg, sizeof(receive_msg) - sizeof(long), 1, 0); // Получаем сообщение

        printf("Полученное сообщение: %s", receive_msg.text);

        // Здесь можно добавить логику для обработки сообщения, например, проверку на специальное значение,
        // которое может служить сигналом к завершению.
    }

    return 0;
}
