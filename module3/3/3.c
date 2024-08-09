#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_FIELD_LENGTH 50

struct Contact {
    char first_name[MAX_FIELD_LENGTH];
    char last_name[MAX_FIELD_LENGTH];
    char email[MAX_FIELD_LENGTH];
    char phone_number[MAX_FIELD_LENGTH];
    char social_media[MAX_FIELD_LENGTH];
    struct MessengerProfile {
        char vk[MAX_FIELD_LENGTH];
        char telegram[MAX_FIELD_LENGTH];
        char instagram[MAX_FIELD_LENGTH];
    } messenger_profile;
};

struct Contact contacts[MAX_CONTACTS];
size_t contactCount = 0;

void readString(char* buffer, size_t bufferSize) {
    fgets(buffer, bufferSize, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

void loadContacts() {
    FILE *file = fopen("contacts.bin", "rb");
    if (!file) return;

    contactCount = fread(contacts, sizeof(struct Contact), MAX_CONTACTS, file);
    fclose(file);
}

void saveContacts() {
    FILE *file = fopen("contacts.bin", "wb");
    if (!file) {
        perror("Ошибка открытия файла для записи");
        return;
    }

    fwrite(contacts, sizeof(struct Contact), contactCount, file);
    fclose(file);
}

void addContact() {
    struct Contact newContact;
    printf("Введите имя: ");
    readString(newContact.first_name, MAX_FIELD_LENGTH);
    printf("Введите фамилию: ");
    readString(newContact.last_name, MAX_FIELD_LENGTH);
    printf("Введите почту: ");
    readString(newContact.email, MAX_FIELD_LENGTH);
    printf("Введите телефон: ");
    readString(newContact.phone_number, MAX_FIELD_LENGTH);
    printf("Введите ссылку на социальные сети: ");
    readString(newContact.social_media, MAX_FIELD_LENGTH);
    printf("Введите VK: ");
    readString(newContact.messenger_profile.vk, MAX_FIELD_LENGTH);
    printf("Введите Telegram: ");
    readString(newContact.messenger_profile.telegram, MAX_FIELD_LENGTH);
    printf("Введите Instagram: ");
    readString(newContact.messenger_profile.instagram, MAX_FIELD_LENGTH);

    contacts[contactCount++] = newContact;
    saveContacts();
}

void deleteContact(size_t index) {
    if (index >= contactCount) return;

    for (size_t i = index; i < contactCount - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    contactCount--;
    saveContacts();
}

void displayContacts() {
    printf("\nСписок контактов:\n");
    for (size_t i = 0; i < contactCount; i++) {
        printf("%zu. Имя: %s %s\n", i + 1, contacts[i].first_name, contacts[i].last_name);
    }
}

void printBinaryData(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    unsigned char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for (size_t i = 0; i < bytesRead; ++i) {
            printf("%02x ", buffer[i]);
        }
        printf("\n");
    }

    fclose(file);
}

int main() {
    loadContacts();

    int choice;
    size_t index;

    do {
        printf("\nМеню:\n");
        printf("1. Добавить контакт\n");
        printf("2. Просмотреть список контактов\n");
        printf("3. Удалить контакт\n");
        printf("4. Вывести бинарные данные файла\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                displayContacts();
                printf("Введите номер контакта для удаления: ");
                scanf("%zu", &index);
                getchar();
                deleteContact(index - 1);
                break;
            case 4:
                printBinaryData("contacts.bin");
                break;
            case 5:
                printf("Выходим из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 5);

    return 0;
}
