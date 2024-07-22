#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct Node {
    struct Contact contact;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

void trim_newline(char* str) {
    char* newline = strchr(str, '\n');
    if (newline) *newline = '\0';
}

void addContact(struct Node** nodePtr, struct Contact contact) {
    if (*nodePtr == NULL) {
        *nodePtr = malloc(sizeof(struct Node));
        (*nodePtr)->contact = contact;
        (*nodePtr)->left = NULL;
        (*nodePtr)->right = NULL;
    } else {
        int compareResult = strcmp(contact.name.last_name, (*nodePtr)->contact.name.last_name);
        if (compareResult < 0) {
            addContact(&((*nodePtr)->left), contact);
        } else if (compareResult > 0) {
            addContact(&((*nodePtr)->right), contact);
        }
    }
}

void displayContacts(struct Node* node) {
    if (node != NULL) {
        displayContacts(node->left);
        printf("Имя: %s %s\n", node->contact.name.first_name, node->contact.name.last_name);
        printf("Email: %s\n", node->contact.email_phone.email);
        printf("Телефон: %s\n", node->contact.email_phone.phone_number);
        printf("Социальные сети: %s\n", node->contact.social_media_profile.social_media);
        printf("VK: %s\n", node->contact.social_media_profile.messenger_profile.vk);
        printf("Telegram: %s\n", node->contact.social_media_profile.messenger_profile.telegram);
        printf("Instagram: %s\n", node->contact.social_media_profile.messenger_profile.instagram);
        displayContacts(node->right);
    }
}

struct Node* findMinNode(struct Node* root) {
    while(root && root->left != NULL)
        root = root->left;
    return root;
}

struct Node* deleteNode(struct Node* root, char* lastName) {
    if (root == NULL) return root;

    if (strcmp(lastName, root->contact.name.last_name) < 0)
        root->left = deleteNode(root->left, lastName);
    else if (strcmp(lastName, root->contact.name.last_name) > 0)
        root->right = deleteNode(root->right, lastName);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMinNode(root->right);

        root->contact = temp->contact;

        root->right = deleteNode(root->right, temp->contact.name.last_name);
    }
    return root;
}

void editContact(struct Node** nodePtr, char* lastName, struct Contact new_contact) {
    if (*nodePtr != NULL) {
        int compareResult = strcmp(lastName, (*nodePtr)->contact.name.last_name);
        if (compareResult < 0) {
            editContact(&((*nodePtr)->left), lastName, new_contact);
        } else if (compareResult > 0) {
            editContact(&((*nodePtr)->right), lastName, new_contact);
        } else {
            (*nodePtr)->contact = new_contact;
        }
    }
}

int main() {
    int choice;
    struct Contact new_contact;

    do {
        printf("\nМеню:\n");
        printf("1. Добавить контакт\n");
        printf("2. Просмотреть список контактов\n");
        printf("3. Редактировать контакт\n");
        printf("4. Удалить контакт\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar(); // Очистка буфера ввода после scanf

        switch (choice) {
            case 1:
                printf("Имя: ");
                fgets(new_contact.name.first_name, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.name.first_name);
                printf("Фамилия: ");
                fgets(new_contact.name.last_name, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.name.last_name);
                printf("Email: ");
                fgets(new_contact.email_phone.email, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.email_phone.email);
                printf("Телефон: ");
                fgets(new_contact.email_phone.phone_number, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.email_phone.phone_number);
                printf("Социальные сети: ");
                fgets(new_contact.social_media_profile.social_media, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.social_media_profile.social_media);
                printf("VK: ");
                fgets(new_contact.social_media_profile.messenger_profile.vk, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.social_media_profile.messenger_profile.vk);
                printf("Telegram: ");
                fgets(new_contact.social_media_profile.messenger_profile.telegram, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.social_media_profile.messenger_profile.telegram);
                printf("Instagram: ");
                fgets(new_contact.social_media_profile.messenger_profile.instagram, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.social_media_profile.messenger_profile.instagram);
                addContact(&root, new_contact);
                break;
            case 2:
                displayContacts(root);
                break;
            case 3:
                printf("Введите фамилию контакта для редактирования: ");
                fgets(new_contact.name.last_name, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.name.last_name);
                printf("Новое имя: ");
                fgets(new_contact.name.first_name, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.name.first_name);
                printf("Новый Email: ");
                fgets(new_contact.email_phone.email, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.email_phone.email);
                printf("Новый Телефон: ");
                fgets(new_contact.email_phone.phone_number, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.email_phone.phone_number);
                printf("Новые социальные сети: ");
                fgets(new_contact.social_media_profile.social_media, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.social_media_profile.social_media);
                printf("Новый VK: ");
                fgets(new_contact.social_media_profile.messenger_profile.vk, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.social_media_profile.messenger_profile.vk);
                printf("Новый Telegram: ");
                fgets(new_contact.social_media_profile.messenger_profile.telegram, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.social_media_profile.messenger_profile.telegram);
                printf("Новый Instagram: ");
                fgets(new_contact.social_media_profile.messenger_profile.instagram, MAX_FIELD_LENGTH, stdin);
                trim_newline(new_contact.social_media_profile.messenger_profile.instagram);
                editContact(&root, new_contact.name.last_name, new_contact);
                break;
            case 4:
                printf("Введите фамилию контакта для удаления: ");
                char lastName[MAX_FIELD_LENGTH];
                fgets(lastName, MAX_FIELD_LENGTH, stdin);
                trim_newline(lastName);
                root = deleteNode(root, lastName);
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
