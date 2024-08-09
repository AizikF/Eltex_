#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct msgbuf {
    long mtype; // Тип сообщения (приоритет)
    long priority; // Приоритет сообщения
    char mtext[100]; // Текст сообщения
};

int main() {
    int msgid;
    struct msgbuf msg;

    // Получение идентификатора очереди сообщений
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    // Цикл получения сообщений
    for (int i = 0; i < 10; ++i) { // Получаем 10 сообщений
        msgrcv(msgid, &msg, sizeof(msg.mtext), i + 1, 0); // Получаем сообщение с определенным типом
        printf("Received message: %s\n", msg.mtext);
    }

    // Удаление очереди сообщений
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
