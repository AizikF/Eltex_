#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#define QUEUE_NAME "/chat_queue"

int main() {
    mqd_t mqdes;
    struct mq_attr attr;
    char buffer[#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 100
#define MSG_KEY 1234
#define FINISH_TYPE 10

struct msgbuf {
    long mtype;
    char text[MSG_SIZE];
};

int main() {
    int msgid;
    struct msgbuf msg;

    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Client is running...\n");

    for (int i = 0; i < 5; ++i) { // Отправляем 5 сообщений
        sprintf(msg.text, "Ping #%d", i + 1);
        msgsnd(msgid, &msg, sizeof(msg), 0);

        msgrcv(msgid, &msg, sizeof(msg), 0, 0); // Ждем ответ от сервера
        printf("Echo from server: %s\n", msg.text);
    }

    // Отправляем сигнал о завершении
    msg.mtype = FINISH_TYPE;
    msgsnd(msgid, &msg, sizeof(msg), 0);

    msgctl(msgid, IPC_RMID, NULL); // Удаляем очередь сообщений
    printf("Client is shutting down.\n");

    return 0;
}
];
    unsigned int prio;

    // Открытие очереди сообщений
    mqdes = mq_open(QUEUE_NAME, O_RDONLY);
    if (mqdes == -1) {#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 100
#define MSG_KEY 1234
#define FINISH_TYPE 10

struct msgbuf {
    long mtype;
    char text[MSG_SIZE];
};

int main() {
    int msgid;
    struct msgbuf msg;

    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Client is running...\n");

    for (int i = 0; i < 5; ++i) { // Отправляем 5 сообщений
        sprintf(msg.text, "Ping #%d", i + 1);
        msgsnd(msgid, &msg, sizeof(msg), 0);

        msgrcv(msgid, &msg, sizeof(msg), 0, 0); // Ждем ответ от сервера
        printf("Echo from server: %s\n", msg.text);
    }

    // Отправляем сигнал о завершении
    msg.mtype = FINISH_TYPE;
    msgsnd(msgid, &msg, sizeof(msg), 0);

    msgctl(msgid, IPC_RMID, NULL); // Удаляем очередь сообщений
    printf("Client is shutting down.\n");

    return 0;
}

        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // Получение сообщения
    if (mq_receive(mqdes, buffer, sizeof(buffer), &prio) == -1) {
        perror("mq_receive");
        exit(EXIT_FAILURE);
    }

    printf("Received message: %s\n", buffer);

    // Закрытие очереди
    if (mq_close(mqdes) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
