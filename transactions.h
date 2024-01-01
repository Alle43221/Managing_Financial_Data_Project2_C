#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "accounts_crud.h"

void save_deposit(struct Node_account* head, char global_user[]);
void save_withdrawal(struct Node_account *head, char user_id[], char  global_user[]);
void save_transfer(struct Node_account* head, char user_id[], char global_user[]);

#endif