#include <stdio.h>
#include "contacts_functions.h"

int main() {
    Node* head = NULL;
    int choice;

    do {
        printf("\nМеню:\n");
        printf("1. Добавить контакт\n");
        printf("2. Просмотреть список контактов\n");
        printf("3. Удалить контакт\n");
        printf("4. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact(&head);
                break;
            case 2:
                displayContacts(head);
                break;
            case 3:
                size_t index;
                printf("Введите номер контакта для его удаления: ");
                scanf("%zu", &index);
                deleteContact(&head, index);
                break;
            case 4:
                printf("Выходим из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 4);

    return 0;
}
