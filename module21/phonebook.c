#include <stdio.h>
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

struct Contact contacts[MAX_CONTACTS];
int num_contacts = 0;

void addContact() {
    if (num_contacts < MAX_CONTACTS) {
        struct Contact new_contact;
        printf("Имя: ");
        fgets(new_contact.name.first_name, MAX_FIELD_LENGTH, stdin);
        printf("Фамилия: ");
        fgets(new_contact.name.last_name, MAX_FIELD_LENGTH, stdin);
        printf("Почта: ");
        fgets(new_contact.email_phone.email, MAX_FIELD_LENGTH, stdin);
        printf("Телефон: ");
        fgets(new_contact.email_phone.phone_number, MAX_FIELD_LENGTH, stdin);
        printf("Ссылка на соц.сети: ");
        fgets(new_contact.social_media_profile.social_media, MAX_FIELD_LENGTH, stdin);
        printf("VK: ");
        fgets(new_contact.social_media_profile.messenger_profile.vk, MAX_FIELD_LENGTH, stdin);
        printf("Telegram: ");
        fgets(new_contact.social_media_profile.messenger_profile.telegram, MAX_FIELD_LENGTH, stdin);
        printf("Instagram: ");
        fgets(new_contact.social_media_profile.messenger_profile.instagram, MAX_FIELD_LENGTH, stdin);

        contacts[num_contacts++] = new_contact;
        printf("Контакт добавлен!\n");
    } else {
        printf("Записная книжка полная. Нельзя добавить больше.\n");
    }
}

void displayContacts() {
    if (num_contacts == 0) {
        printf("Записная книжка пустая.\n");
    } else {
        for (size_t i = 0; i < num_contacts; i++) {
            printf("\nКонтакт%zu:\n", i + 1);
            printf("Имя: %s %s\n", contacts[i].name.first_name, contacts[i].name.last_name);
            printf("Почта: %s\n", contacts[i].email_phone.email);
            printf("Телефон: %s\n", contacts[i].email_phone.phone_number);
            printf("Соц.сети: %s\n", contacts[i].social_media_profile.social_media);
            printf("VK: %s\n", contacts[i].social_media_profile.messenger_profile.vk);
            printf("Telegram: %s\n", contacts[i].social_media_profile.messenger_profile.telegram);
            printf("Instagram: %s\n", contacts[i].social_media_profile.messenger_profile.instagram);
        }
    }
}

void editContact() {
    if (num_contacts > 0) {
        size_t index;
        printf("Введите номер контакта для его редактирования: ");
        scanf("%zu", &index);

        if (index >= 0 && index < num_contacts) {
            struct Contact updated_contact;
            printf("Новое имя: ");
            fgets(updated_contact.name.first_name, MAX_FIELD_LENGTH, stdin);
            printf("Новая фамилия: ");
            fgets(updated_contact.name.last_name, MAX_FIELD_LENGTH, stdin);
            printf("Новая почта: ");
            fgets(updated_contact.email_phone.email, MAX_FIELD_LENGTH, stdin);
            printf("Новый телефон: ");
            fgets(updated_contact.email_phone.phone_number, MAX_FIELD_LENGTH, stdin);
            printf("Новая ссылка на соц.сети: ");
            fgets(updated_contact.social_media_profile.social_media, MAX_FIELD_LENGTH, stdin);
            printf("Новый VK: ");
            fgets(updated_contact.social_media_profile.messenger_profile.vk, MAX_FIELD_LENGTH, stdin);
            printf("Новый Telegram: ");
            fgets(updated_contact.social_media_profile.messenger_profile.telegram, MAX_FIELD_LENGTH, stdin);
            printf("Новый Instagram: ");
            fgets(updated_contact.social_media_profile.messenger_profile.instagram, MAX_FIELD_LENGTH, stdin);

            contacts[index] = updated_contact;
            printf("Контакт успешно обновлен!\n");
        } else {
            printf("Указанный индекс не найден. Проверьте правильность введенных данных.\n");
        }
    } else {
        printf("Нет контактов для редактирования. Добавьте хотя бы один контакт.\n");
    }
}

void deleteContact() {
    if (num_contacts > 0) {
        size_t index;
        printf("Введите номер контакта для его удаления: ");
        scanf("%zu", &index);

        if (index >= 0 && index < num_contacts) {
            for (size_t i = index; i < num_contacts - 1; i++) {
                contacts[i] = contacts[i + 1];
            }
            num_contacts--;
            printf("Контакт успешно удален!\n");
        } else {
            printf("Указанный индекс не найден. Проверьте правильность введенных данных.\n");
        }
    } else {
        printf("Нет контактов для удаления. Добавьте хотя бы один контакт.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\nМеню:\n");
        printf("1. Добавить контакт\n");
        printf("2. Редактировать контакт\n");
        printf("3. Просмотреть список контактов\n");
        printf("4. Удалить контакт\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                editContact();
                break;
            case 3:
                displayContacts();
                break;
            case 4:
                deleteContact();
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
