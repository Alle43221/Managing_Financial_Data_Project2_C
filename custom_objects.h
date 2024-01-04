#ifndef CUSTOM_OBJECTS_H
#define CUSTOM_OBJECTS_H
#include <stdio.h>
#include <string.h>
#include "stdlib.h"

struct customer{
    /**
     * structure containing data for a customer
     */
    char name[50], iban[25], phone[11], id_string[10], email[50];
};

struct Node_customer{
    /**
     * node structure for dynamically allocated list consisting of customer objects
     */
    struct customer data;
    struct Node_customer* next;
};

struct account{
    /**
     * structure containing data for an account
     */
    char type;
    float balance;
    char iban[25];
};

struct Node_account{
    /**
     * node structure for dynamically allocated list consisting of account objects
     */
    struct account data;
    struct Node_account* next;
};

struct user{
    /**
     * structure containing data for a user
     */
    char id[17], username[50], password[30];
};

struct Node_user{
    /**
     * node structure for dynamically allocated list consisting of user objects
     */
    struct user data;
    struct Node_user* next;
};


#endif