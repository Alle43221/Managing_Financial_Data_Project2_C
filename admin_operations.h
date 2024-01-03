#ifndef ADMIN_OPERATIONS_H
#define ADMIN_OPERATIONS_H
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "validation.h"
#include <direct.h>
#include "windows.h"

void select_user_admin(char global_user[], char user_id[]);
void add_user(char global_user[]);

#endif