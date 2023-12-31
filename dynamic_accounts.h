#ifndef DYNAMIC_ACCOUNTS_H
#define DYNAMIC_ACCOUNTS_H
#include "custom_objects.h"
#include "math.h"

int check_id_account(struct Node_account* head, char new_id[]);
struct Node_account* insert_at_end_account(struct Node_account* head, char type[], char iban[], float value);
struct Node_account* delete_by_id_account(struct Node_account* head, char id[]);
void modify_account_by_id(struct Node_account *head, char id_string[], float value);

#endif