#ifndef CUSTOMERS_CRUD_H
#define CUSTOMERS_CRUD_H

#include "dynamic_customers.h"
#include "validation.h"
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "time.h"

void save_customers_to_file(struct Node_customer *head, char global_user[]);
struct Node_customer* delete_customer(struct Node_customer *head, char global_user[]);
void modify_customer(struct Node_customer *head, char global_user[]);
struct Node_customer* add_customer(struct Node_customer *head, char global_user[]);
struct Node_customer* load_customers(struct Node_customer *head, char global_user[]);
void print_all_customers(struct Node_customer *head);
#endif