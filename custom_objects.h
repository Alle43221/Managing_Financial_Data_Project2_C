#ifndef CUSTOM_OBJECTS_H
#define CUSTOM_OBJECTS_H
#include <stdio.h>
#include <string.h>
#include "stdlib.h"

struct customer{
    char name[50], iban[25], phone[11], id_string[10], email[50];
};

struct Node_customer{
    struct customer data;
    struct Node_customer* next;
};

struct account{
    char type;
    float balance;
    char iban[25];
};

struct Node_account{
    struct account data;
    struct Node_account* next;
};


#endif