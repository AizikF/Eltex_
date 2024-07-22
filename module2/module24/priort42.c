#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

typedef struct Node {
    char message[100];
    int32_t priority;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DblLinkedList {
    Node* head;
    Node* tail;
    size_t size;
} DblLinkedList;

DblLinkedList* createDblLinkedList() {
    DblLinkedList *tmp = (DblLinkedList*) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}

void deleteDblLinkedList(DblLinkedList **list) {
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void pushFront(DblLinkedList *list, Node* tmp) {
    if (tmp == NULL) {
        exit(1);
    }
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;
    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
}

Node* popFront(DblLinkedList *list) {
    Node *prev;
    if (list->head == NULL) {
        exit(2);
    }
    prev = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }
    list->size--;
    return prev;
}

void pushBack(DblLinkedList *list, Node* tmp) {
    if (tmp == NULL) {
        exit(3);
    }
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;
    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}

Node* popBack(DblLinkedList *list) {
    Node *next;
    if (list->tail == NULL) {
        exit(4);
    }
    next = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    list->size--;
    return next;
}

void printDblLinkedList(DblLinkedList *list, void (*fun)(Node*)) {
    if (list->size != 0) {
        Node *tmp = list->head;
        int n = 1;
        while (tmp) {
            printf("Сообщение %d\n", n++);
            fun(tmp);
            tmp = tmp->next;
        }
        printf("\n");
    } else {
        printf("Нет сообщений\n\n");
    }
}

void printListContact(struct Node* contact) {
    printf("сообщение - %s | приоритет - %d\n", contact->message, contact->priority);
}

Node* popFrontPriority(DblLinkedList **list, int32_t priority) {
    Node *elm = (*list)->head;
    if (!elm) return NULL;
    while (elm) {
        if (elm->priority == priority) {
            if (elm->prev) {
                elm->prev->next = elm->next;
            }
            if (elm->next) {
                elm->next->prev = elm->prev;
            }
            if (!elm->prev) {
                (*list)->head = elm->next;
            }
            if (!elm->next) {
                (*list)->tail = elm->prev;
            }
            (*list)->size--;
            return elm;
        }
        elm = elm->next;
    }
    printf("Нет задачи с данным приоритетом\n");
    return NULL;
}

Node* popFrontPriorityMore(DblLinkedList **list, int32_t priority) {
    Node *elm = (*list)->head;
    Node *next = NULL;
    while (elm) {
        if (elm->priority >= priority) {
            if (elm->prev) {
                elm->prev->next = elm->next;
            }
            if (elm->next) {
                elm->next->prev = elm->prev;
            }
            if (!elm->prev) {
                (*list)->head = elm->next;
            }
            if (!elm->next) {
                (*list)->tail = elm->prev;
            }
            (*list)->size--;
            return elm;
        }
        next = elm->next;
        elm = next;
    }
    printf("Нет задачи с данным приоритетом\n");
    return NULL;
}

int main() {
    srand(time(NULL));
    const int32_t N = rand() % 25;
    DblLinkedList *queue = createDblLinkedList();
    Node* test;

    for (int32_t i = 0; i < N; i++) {
        Node *tmp = (Node*) malloc(sizeof(Node));
        strcpy(tmp->message, "test");
        tmp->priority = rand() % 256;
        pushBack(queue, tmp);
    }
    printDblLinkedList(queue, printListContact);

    if ((test = popFront(queue)) != NULL) {
        printf("\nПервый элемент\n");
        printListContact(test);
        free(test);
        printf("\n");
    } else {
        printf("нет элемента\n");
    }

    printDblLinkedList(queue, printListContact);

    int32_t priority;
    printf("Введите приоритет задачи(0-255): ");
    scanf("%d", &priority);
    if ((test = popFrontPriority(&queue, priority)) != NULL) {
        printf("\nэлемент с указанным приоритетом\n");
        printListContact(test);
        free(test);
    } else {
        printf("нет элемента\n");
    }

    printf("\n");
    printDblLinkedList(queue, printListContact);

    printf("Введите приоритет задачи(Для задач с приоритетом не меньше заданного 0-255): ");
    scanf("%d", &priority);
    if ((test = popFrontPriorityMore(&queue, priority)) != NULL) {
        printf("\nэлемент с приоритетом не ниже\n");
        printListContact(test);
        free(test);
    } else {
        printf("нет элемента\n");
    }

    deleteDblLinkedList(&queue); // Освобождение памяти
    return 0;
}
