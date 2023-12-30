#ifndef DYNAMIC_ACCOUNTS_H
#define DYNAMIC_ACCOUNTS_H
#include "custom_objects.h"

int check_id_account(struct Node_account* head, char new_id[]);
struct Node_account* insert_at_end_account(struct Node_account* head, char type[], char iban[], float value);
struct Node_account* delete_by_id_account(struct Node_account* head, char id[]);

#endif