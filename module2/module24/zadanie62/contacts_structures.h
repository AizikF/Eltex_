// contacts_structures.h

#ifndef CONTACTS_STRUCTURES_H
#define CONTACTS_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>

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

#endif // CONTACTS_STRUCTURES_H
