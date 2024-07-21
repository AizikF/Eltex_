// contacts_functions.h

#ifndef CONTACTS_FUNCTIONS_H
#define CONTACTS_FUNCTIONS_H

#include "contacts_structures.h"

void removeNewlineChar(char* str);
void clearInputBuffer();
Node* createNode(struct Contact contact);
void addContact(Node** head);
void displayContacts(Node* head);
void deleteContact(Node** head, size_t index);

#endif // CONTACTS_FUNCTIONS_H
