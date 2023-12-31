
#ifndef DYNAMIC_CUSTOMERS_H
#define DYNAMIC_CUSTOMERS_H
#include "custom_objects.h"
#include <sys/types.h>

int check_id_customer(struct Node_customer* head, char new_id[]);
void modify_by_id_customer(struct Node_customer* head, char id[], char name[], char iban[], char phone[], char email[]);
struct Node_customer* insert_at_end_customer(struct Node_customer* head, char name[], char iban[], char phone[], char id[], char email[]);
struct Node_customer* delete_by_id_customer(struct Node_customer* head, char id[]);

#endif