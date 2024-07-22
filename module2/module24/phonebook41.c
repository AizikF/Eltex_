#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_FIELD_LENGTH 50

struct Name {
    char first_name[MAX_FIELD_LENGTH];
    char last_name[MAX_FIELD_LENGTH];
};

struct EmailPhone {
    char email[MAX_FIELD_LENGTH];
    char phone_number[MAX_FIELD_LENGTH];
};

struct SocialMediaProfile {
    char social_media[MAX_FIELD_LENGTH];
    struct MessengerProfile {
        char vk[MAX_FIELD_LENGTH];
        char telegram[MAX_FIELD_LENGTH];
        char instagram[MAX_FIELD_LENGTH];
    } messenger_profile;
};

struct Contact {
    struct Name name;
    struct EmailPhone email_phone;
    struct SocialMediaProfile social_media_profile;
};

typedef struct Node {
    struct Contact contact;
    struct Node* next;
    struct Node* prev;
} Node;

Node* head = NULL;

void removeNewlineChar(char* str) {
    char *newline = strchr(str, '\n');
    if (newline) *newline = '\0';
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addContact() {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Ошибка выделения памяти.\n");
        return;
    }
    memset(newNode->contact.name.first_name, 0, MAX_FIELD_LENGTH);
    newNode->next = NULL;
    newNode->prev = NULL;

    printf("Введите имя: ");
    fgets(newNode->contact.name.first_name, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newNode->contact.name.first_name);
    printf("Введите фамилию: ");
    fgets(newNode->contact.name.last_name, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newNode->contact.name.last_name);
    printf("Введите почту: ");
    fgets(newNode->contact.email_phone.email, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newNode->contact.email_phone.email);
    printf("Введите телефон: ");
    fgets(newNode->contact.email_phone.phone_number, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newNode->contact.email_phone.phone_number);
    printf("Введите ссылку на социальные сети: ");
    fgets(newNode->contact.social_media_profile.social_media, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newNode->contact.social_media_profile.social_media);
    printf("Введите VK: ");
    fgets(newNode->contact.social_media_profile.messenger_profile.vk, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newNode->contact.social_media_profile.messenger_profile.vk);
    printf("Введите Telegram: ");
    fgets(newNode->contact.social_media_profile.messenger_profile.telegram, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newNode->contact.social_media_profile.messenger_profile.telegram);
    printf("Введите Instagram: ");
    fgets(newNode->contact.social_media_profile.messenger_profile.instagram, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newNode->contact.social_media_profile.messenger_profile.instagram);

    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void displayContacts() {
    Node* current = head;
    while (current != NULL) {
        printf("\nКонтакт:\n");
        printf("Имя: %s %s\n", current->contact.name.first_name, current->contact.name.last_name);
        printf("Почта: %s\n", current->contact.email_phone.email);
        printf("Телефон: %s\n", current->contact.email_phone.phone_number);
        printf("Социальные сети: %s\n", current->contact.social_media_profile.social_media);
        printf("VK: %s\n", current->contact.social_media_profile.messenger_profile.vk);
        printf("Telegram: %s\n", current->contact.social_media_profile.messenger_profile.telegram);
        printf("Instagram: %s\n", current->contact.social_media_profile.messenger_profile.instagram);
        current = current->next;
    }
}

void deleteContact(size_t index) {
    if (!head) {
        printf("Список контактов пуст.\n");
        return;
    }

    Node* temp = head;
    for (size_t i = 0; i < index && temp != NULL; i++) {
        temp = temp->next;
    }

    if (!temp) {
        printf("Указанный индекс не найден.\n");
        return;
    }

    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }
    if (temp->next) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    printf("Контакт успешно удален!\n");
}

int main() {
    int choice;

    do {
        printf("\nМеню:\n");
        printf("1. Добавить контакт\n");
        printf("2. Просмотреть список контактов\n");
        printf("3. Удалить контакт\n");
        printf("4. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                size_t index;
                printf("Введите номер контакта для его удаления: ");
                scanf("%zu", &index);
                clearInputBuffer();
                deleteContact(index);
                break;
            case 4:
                printf("Выходим из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 4);

    Node* temp = head;
    while (temp != NULL) {
        Node* nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    return 0;
}
