
#ifndef VALIDATION_H
#define VALIDATION_H

struct customer{
    char name[50], iban[25], phone[11], id_string[10], email[50];
};

struct Node_customer{
    struct customer data;
    struct Node_customer* next;
};

int check_id_customer(struct Node_customer*, char[]);

int validare_string(char[]);

int validare_iban(char[]);

int validare_phone(char[]);

int validare_id_customer(char[], struct Node_customer*);

int validare_email(char[]);

#endif