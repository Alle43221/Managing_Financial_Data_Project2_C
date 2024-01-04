#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "customers_crud.h"
#include "transactions.h"
#include "reports.h"
#include "admin_operations.h"
#include "time.h"

void login_menu(char global_user[], char user_id[])
{
    /**
     * param: none
     * description: login function for the app
     * exception: invalid password -> new login
     *            invalid username -> new login
     *            Error opening file at path
     * return: none
     */
    FILE *file=fopen("users.csv", "r");
    if(file==NULL){
        printf("Error opening file at users.csv\n");
        return;
    }
    char username[50], password[30], buffer[100];
    char username1[50], password1[30];
    printf("Enter username:\n");
    gets( username);
    if(strcmp(username, "exit")==0){
        strcpy(global_user,"exit");
        return;
    }

    printf("Enter password:\n");
    gets(password);
    while(fgets(buffer, 100, file)){
        strcpy(username1, strtok(buffer, ",\n"));
        strcpy(password1, strtok(NULL, ",\n"));
        strcpy(user_id, strtok(NULL, ",\n"));
        if(strcmp(username, username1)==0){
            if(strcmp(password, password1)==0){
                printf("Login successfully!\n");
                strcpy(global_user, username);

                char path[100];
                sprintf(path, "./%s/log.txt",username);

                FILE *file1=fopen(path, "a");
                time_t t;
                time(&t);
                char str[100];
                sprintf(str, "Login at %s",ctime(&t));
                fwrite(str, 1, strlen(str), file1);
                fclose(file1);

                fclose(file);
                return;
            }
            else{
                printf("Invalid password!\n");
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    printf("Invalid username!\n");
}

void welcome_text(){
    /**
    * param: none
    * description: prints a welcome message for the user
    * return: none
    */
    printf("---------------------------------------------\n");
    printf("| Welcome to the transaction manager!       |\n");
    printf("| Please follow the bellow steps to log in. |\n");
    printf("| Or type \"exit\" to stop the program.       |\n");
    printf("---------------------------------------------\n");
}

void menu_text(){
    /**
    * param: none
    * description: prints a list of menu options for the user
    * return: none
    */
    printf("---------------------------------------------\n");
    printf("| Menu:                                     |\n");
    printf("---------------------------------------------\n");
    printf("| 1. Add customer                           |\n");
    printf("| 2. Delete customer                        |\n");
    printf("| 3. Modify customer                        |\n");
    printf("| 4. Print all customers                    |\n");
    printf("---------------------------------------------\n");
    printf("| 5. Create account                         |\n");
    printf("| 6. Delete account                         |\n");
    printf("| 7. Print all accounts                     |\n");
    printf("| 8. Check account balance                  |\n");
    printf("---------------------------------------------\n");
    printf("| 9. Save deposit                           |\n");
    printf("| 10. Save withdrawal                       |\n");
    printf("| 11. Save transaction                      |\n");
    printf("---------------------------------------------\n");
    printf("| 12. Generate account statement            |\n");
    printf("| 13. Generate transaction register         |\n");
    printf("| 14. Generate expense report               |\n");
    printf("---------------------------------------------\n");
    printf("| 15. Log out                               |\n");
    printf("---------------------------------------------\n");
    printf("| Admin options:                            |\n");
    printf("---------------------------------------------\n");
    printf("| 16. Add client                            |\n");
    printf("---------------------------------------------\n");
}

int main(){
    /**
     * param: none
     * description: console interface for transaction app
     * exception: ends the program on input "exit"
     */

    char global_user[50]="";
    char user_id[17]="";
    struct Node_customer* customers_head=NULL;
    struct Node_account* accounts_head=NULL;
    char menu_choice[100];
    welcome_text();
    while(strlen(global_user)==0){
        login_menu(global_user, user_id);
    }
    if(strcmp(global_user, "exit")==0){
        return 0;
    }
    customers_head=load_customers(customers_head, global_user);
    accounts_head=load_accounts(accounts_head, global_user);
    menu_text();
    while(strcmp(menu_choice, "exit")!=0){
        gets(menu_choice);
        if(strcmp(menu_choice,"1")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            customers_head=add_customer(customers_head, global_user);
        }
        else if(strcmp(menu_choice,"2")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            customers_head=delete_customer(customers_head, global_user);
        }
        else if(strcmp(menu_choice,"3")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            modify_customer(customers_head, global_user);
        }
        else if(strcmp(menu_choice,"4")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            print_all_customers(customers_head);
        }
        else if(strcmp(menu_choice,"5")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            accounts_head=add_account(accounts_head, global_user, user_id);
        }
        else if(strcmp(menu_choice,"6")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            accounts_head=delete_account(accounts_head, global_user);
        }
        else if(strcmp(menu_choice,"7")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            print_all_accounts(accounts_head);
        }
        else if(strcmp(menu_choice,"8")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            check_account_balance(accounts_head);
        }
        else if(strcmp(menu_choice,"9")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            save_deposit(accounts_head, global_user);
        }
        else if(strcmp(menu_choice,"10")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            save_withdrawal(accounts_head, user_id, global_user);
        }
        else if(strcmp(menu_choice,"11")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            save_transfer(accounts_head, user_id, global_user);
        }
        else if(strcmp(menu_choice,"12")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            generate_account_statement(global_user, accounts_head);
        }
        else if(strcmp(menu_choice,"13")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            generate_transaction_register(global_user, accounts_head);
        }
        else if(strcmp(menu_choice,"14")==0){
            if(strcmp("admin", global_user)==0){
                while(strcmp("admin", global_user)==0){
                    printf("Please select the user for which you want to access the files\n");
                    select_user_admin(global_user, user_id);
                }
                printf("User changed to %s\n", global_user);
                customers_head=load_customers(customers_head, global_user);
                accounts_head=load_accounts(accounts_head, global_user);
            }
            generate_expense_report(global_user, accounts_head);
        }
        else if(strcmp(menu_choice,"15")==0){
            printf("Successfully logged out!\n");
            strcpy(global_user, "");
            welcome_text();
            while(strlen(global_user)==0){
                login_menu(global_user, user_id);
            }
            customers_head=load_customers(customers_head, global_user);
            accounts_head=load_accounts(accounts_head, global_user);
            menu_text();
        }
        else if(strcmp(menu_choice,"16")==0) {
            add_user(global_user);
        }
        else if(strcmp(menu_choice,"exit")==0){
            return 0;
        }
        else{
            printf("Invalid option!\n");
        }
    }
    return 0;
}