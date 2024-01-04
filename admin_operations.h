#ifndef ADMIN_OPERATIONS_H
#define ADMIN_OPERATIONS_H
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "validation.h"
#include <direct.h>
#include "windows.h"
#include "custom_objects.h"
#include "dynamic_users.h"
#include "time.h"

void select_user_admin(char global_user[], char user_id[]);
struct Node_user* add_user(struct Node_user* head);

struct Node_user * load_users(struct Node_user *head);
void save_users_to_file(struct Node_user *head);
struct Node_user * delete_user(struct Node_user *head);
void reset_password(struct Node_user *head);

#endif