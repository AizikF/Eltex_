#ifndef CONTACTS_LIBRARY_H
#define CONTACTS_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD_LENGTH 50

typedef struct Name {
    char first_name[MAX_FIELD_LENGTH];
    char last_name[MAX_FIELD_LENGTH];
} Name;

typedef struct EmailPhone {
    char email[MAX_FIELD_LENGTH];
    char phone_number[MAX_FIELD_LENGTH];
} EmailPhone;

typedef struct SocialMediaProfile {
    char social_media[MAX_FIELD_LENGTH];
    typedef struct MessengerProfile {
        char vk[MAX_FIELD_LENGTH];
        char telegram[MAX_FIELD_LENGTH];
        char instagram[MAX_FIELD_LENGTH];
    } MessengerProfile;
    MessengerProfile messenger_profile;
} SocialMediaProfile;

typedef struct Contact {
    Name name;
    EmailPhone email_phone;
    SocialMediaProfile social_media_profile;
} Contact;

typedef struct Node {
    Contact contact;
    struct Node* next;
    struct Node* prev;
} Node;

void removeNewlineChar(char* str);
void clearInputBuffer();
void addContact(Node** head);
void displayContacts(Node* head);
void deleteContact(Node** head, size_t index);

#endif // CONTACTS_LIBRARY_H
