
#ifndef DYNAMIC_CUSTOMERS_H
#define DYNAMIC_CUSTOMERS_H
#include "validation.h"

int check_id_customer(struct Node_customer* head, char new_id[]);
void modify_by_id_customer(struct Node_customer* head, char id[], char name[], char iban[], char phone[], char email[]);

#endif