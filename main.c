#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <direct.h>
#include "windows.h"
#include "customers_crud.h"
#include "accounts_crud.h"
#include "transactions.h"

void login_menu(char global_user[], char user_id[])
{
    /**
     * param: none
     * description: login function for the app
     * exception: invalid password -> new login
     *            invalid username -> new login
     * return: none
     */
    FILE *file=fopen("users.txt", "r");
    char username[50], password[50], buffer[100];
    char username1[50], password1[50];
    printf("Enter username:\n");
    scanf("%50s", username);
    printf("Enter password:\n");
    scanf("%50s", password);
    while(fgets(buffer, 100, file)){
        strcpy(username1, strtok(buffer, " \n"));
        strcpy(password1, strtok(NULL, " \n"));
        strcpy(user_id, strtok(NULL, " \n"));
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
    printf("| 12. Log out                               |\n");
    printf("---------------------------------------------\n");
    printf("| Admin options:                            |\n");
    printf("---------------------------------------------\n");
    printf("| 13. Add client                             |\n");
    printf("---------------------------------------------\n");
}

int check_username(char user[]){
    FILE *file=fopen("users.txt", "r");
    if(file==NULL){
        printf("Error opening file at %s\n", "users.txt");
        return 0;
    }
    char username[50], password[50], buffer[100], user_id[17];
    while(fgets(buffer, 100, file)) {
        strcpy(username, strtok(buffer, " \n"));
        strcpy(password, strtok(NULL, " \n"));
        strcpy(user_id, strtok(NULL, " \n"));
        if(strcmp(user, username)==0){
            return 0;
        }
    }
    return 1;
}

int check_user_id(char id[17]) {
    FILE *file=fopen("users.txt", "r");
    if(file==NULL){
        printf("Error opening file at %s\n", "users.txt");
        return 0;
    }
    char username[50], password[50], buffer[100], user_id[17];
    while(fgets(buffer, 100, file)) {
        strcpy(username, strtok(buffer, " \n"));
        strcpy(password, strtok(NULL, " \n"));
        strcpy(user_id, strtok(NULL, " \n"));
        if(strcmp(id, user_id)==0){
            return 0;
        }
    }
    return 1;
}

int validate_password(char pass[]){
    if(strlen(pass)<4)
        return 0;
    int l= strlen(pass);
    for (int i=0; i<l; i++){
        if(pass[i]==' '){
            return 0;
        }
    }
    return 1;
}

void add_user(char global_user[]){
    /**
     * param: char[]
     * description: creates a new user with a given username, id and password and all the required functions for it
     * return: void
     * exceptions: Permission denied
     */
    if(strcmp(global_user, "admin")==0){
        char username[50], string_id[17], password[50]="";
        int username1=0, id=0;
        while(username1==0){
            printf("Enter username:\n");
            scanf("%50s", username);
            username1+= validare_string(username);
            username1+= check_username(username);
            if(username1!=2){
                printf("Invalid username!\n");
                username1=0;
            }
        }
        while(id==0){
            printf("Enter id:\n");
            scanf("%17s", string_id);
            id+= validare_id(string_id);
            id+=check_user_id(string_id);
            if(id!=2 || strlen(string_id)!=16){
                printf("Invalid id!\n");
                id=0;
            }
        }
        while(strlen(password)<4){
            printf("Enter password:\n");
            scanf("%17s", password);
            if(validate_password(password)==0){
                printf("Password must be at least 4 characters long and cannot contain spaces!\n");
            }
        }
        _mkdir(username);
        char path[100];
        sprintf(path, "./%s/log.txt",username);
        FILE *file1=fopen(path, "w");
        sprintf(path, "./%s/accounts.txt",username);
        FILE *file2=fopen(path, "w");
        sprintf(path, "./%s/customers.txt",username);
        FILE *file3=fopen(path, "w");
        sprintf(path, "./%s/transactions.txt",username);
        FILE *file4=fopen(path, "w");
        fclose(file1);
        fclose(file2);
        fclose(file3);
        fclose(file4);

        sprintf(path, "users.txt");
        FILE *file5=fopen(path, "a");
        char str[100];
        sprintf(str, "%s %s %s\n", username, password, string_id);
        fwrite(str, 1, strlen(str), file5);
        fclose(file5);
    }
    else{
        printf("Permission denied!\n");
    }
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
    customers_head=load_customers(customers_head, global_user);
    accounts_head=load_accounts(accounts_head, global_user);
    menu_text();
    while(strcmp(menu_choice, "exit")!=0){
        scanf("%100s", menu_choice);
        if(strcmp(menu_choice,"1")==0){
            if(strcmp("admin", global_user)==0){
                //global_user=select_user_admin();
            }
            customers_head=add_customer(customers_head, global_user);
        }
        else if(strcmp(menu_choice,"2")==0){
            customers_head=delete_customer(customers_head, global_user);
        }
        else if(strcmp(menu_choice,"3")==0){
            modify_customer(customers_head, global_user);
        }
        else if(strcmp(menu_choice,"4")==0){
            print_all_customers(customers_head);
        }
        else if(strcmp(menu_choice,"5")==0){
            accounts_head=add_account(accounts_head, global_user, user_id);
        }
        else if(strcmp(menu_choice,"6")==0){
            accounts_head=delete_account(accounts_head, global_user);
        }
        else if(strcmp(menu_choice,"7")==0){
            print_all_accounts(accounts_head);
        }
        else if(strcmp(menu_choice,"8")==0){
            check_account_balance(accounts_head);
        }
        else if(strcmp(menu_choice,"9")==0){
            save_deposit(accounts_head, global_user);
        }
        else if(strcmp(menu_choice,"10")==0){
            save_withdrawal(accounts_head, user_id, global_user);
        }
        else if(strcmp(menu_choice,"11")==0){
            save_transfer(accounts_head, user_id, global_user);
        }
        else if(strcmp(menu_choice,"12")==0){
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
        else if(strcmp(menu_choice,"13")==0) {
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