#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contacts_structures.h" 

void removeNewlineChar(char* str) {
    char *newline = strchr(str, '\n');
    if (newline) *newline = '\0';
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Node* createNode(struct Contact contact) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Ошибка выделения памяти.\n");
        return NULL;
    }
    newNode->contact = contact;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void addContact(Node** head) {
    struct Contact newContact;
    printf("Введите имя: ");
    fgets(newContact.name.first_name, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newContact.name.first_name);
    printf("Введите фамилию: ");
    fgets(newContact.name.last_name, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newContact.name.last_name);
    printf("Введите почту: ");
    fgets(newContact.email_phone.email, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newContact.email_phone.email);
    printf("Введите телефон: ");
    fgets(newContact.email_phone.phone_number, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newContact.email_phone.phone_number);
    printf("Введите ссылку на социальные сети: ");
    fgets(newContact.social_media_profile.social_media, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newContact.social_media_profile.social_media);
    printf("Введите VK: ");
    fgets(newContact.social_media_profile.messenger_profile.vk, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newContact.social_media_profile.messenger_profile.vk);
    printf("Введите Telegram: ");
    fgets(newContact.social_media_profile.messenger_profile.telegram, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newContact.social_media_profile.messenger_profile.telegram);
    printf("Введите Instagram: ");
    fgets(newContact.social_media_profile.messenger_profile.instagram, MAX_FIELD_LENGTH, stdin);
    removeNewlineChar(newContact.social_media_profile.messenger_profile.instagram);

    Node* newNode = createNode(newContact);
    if (!(*head)) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void displayContacts(Node* head) {
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

void deleteContact(Node** head, size_t index) {
    if (!(*head)) {
        printf("Список контактов пуст.\n");
        return;
    }

    Node* temp = *head;
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
        *head = temp->next;
    }
    if (temp->next) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    printf("Контакт успешно удален!\n");
}
