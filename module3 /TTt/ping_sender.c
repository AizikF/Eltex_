#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 1024
#define MSG_KEY 1234 // Используем тот же ключ, что и у получателя

struct msg_buffer {
    long message_type;
    char text[MSG_SIZE];
};

int main() {
    struct msg_buffer send_msg;
    int msgid;

    // Получаем дескриптор очереди сообщений
    msgid = msgget(MSG_KEY, 0666);

    while (1) { // Бесконечный цикл для непрерывной отправки сообщений
        printf("Введите сообщение: ");
        fgets(send_msg.text, MSG_SIZE, stdin); // Чтение строки ввода

        send_msg.message_type = 1; // Тип сообщения

        msgsnd(msgid, &send_msg, sizeof(send_msg) - sizeof(long), 0); // Отправляем сообщение

        printf("Сообщение отправлено.\n");
    }

    return 0;
}
