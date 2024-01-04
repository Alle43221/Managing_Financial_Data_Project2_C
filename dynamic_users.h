#ifndef DYNAMIC_USERS_H
#define DYNAMIC_USERS_H
#include "custom_objects.h"

struct Node_user* insert_at_end_user(struct Node_user* head, char id[], char username[], char password[]);
struct Node_user* delete_by_id_user(struct Node_user* head, char id[]);
void modify_user_by_id(struct Node_user *head, char id_string[], char pass[]);

#endif