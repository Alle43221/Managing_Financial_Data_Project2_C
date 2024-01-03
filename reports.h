#ifndef REPORTS_H
#define REPORTS_H
#include "accounts_crud.h"
#include "ctype.h"

int check_date_in_interval(struct tm start_date, struct tm end_date, struct tm item);
struct tm transform_char_to_tm(char s[]);
void generate_account_statement(char global_user[], struct Node_account* head);
int validate_date(char s[]);
int validate_date_format(char s[]);
int validate_second_date(struct tm end_date, struct tm start_date);
void generate_transaction_register(char global_user[], struct Node_account* head);

#endif