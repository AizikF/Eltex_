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

    // Цикл отправки сообщений
    for (int i = 0; i < 10; ++i) { // Отправляем 10 сообщений
        msg.mtype = i + 1; // Используем номер итерации как приоритет
        msg.priority = i + 1; // Приоритет сообщения
        sprintf(msg.mtext, "Message %d from sender!", i + 1);
        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
        printf("Sent message: %s\n", msg.mtext);
    }

    // Удаление очереди сообщений
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
