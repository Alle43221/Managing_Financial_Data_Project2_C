#ifndef ACCOUNTS_CRUD_H
#define ACCOUNTS_CRUD_H
#include "dynamic_accounts.h"
#include "time.h"
#include "validation.h"

struct Node_account* add_account(struct Node_account *head, char global_user[], char id_client[]);
struct Node_account * load_accounts(struct Node_account *head, char global_user[]);
void print_all_accounts(struct Node_account *head);
void save_accounts_to_file(struct Node_account *head, char global_user[]);
struct Node_account * delete_account(struct Node_account *head, char global_user[]);

#endif

