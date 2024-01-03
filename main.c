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
    FILE *file=fopen("users.txt", "r");
    if(file==NULL){
        printf("Error opening file at users.txt\n");
        return;
    }
    char username[50], password[50], buffer[100];
    char username1[50], password1[50];
    printf("Enter username:\n");
    scanf("%50s", username);
    if(strcmp(username, "exit")==0){
        strcpy(global_user,"exit");
        return;
    }

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

void generate_transaction_register(char global_user[], struct Node_account* head) {
    /**
     * param: char[], struct Node_account*
     * description: generates a transaction record containing basic information about account (iban),
     *                  interval of time for transactions (user input)
     *              saves the report in a new file named transaction-<date and time>.txt
     * return: none
     */
    char iban[25], date1[10], date2[10];
    int iban1=0, date_1=0, date_2=0;
    while(iban1==0){
        printf("Enter the account iban:\n");
        scanf("%25s", iban);
        iban1+=validare_iban(iban);
        if(iban1==0){
            printf("Invalid iban!\n");
        }
    }
    while(date_1==0){
        printf("Enter the start date (format DD:MM:YYYY):\n");
        scanf("%10s", date1);
        date_1+= validate_date_format(date1);
        date_1+= validate_date(date1);
        if(date_1!=2){
            printf("Invalid date!\n");
            date_1=0;
        }
    }
    struct tm info= transform_char_to_tm(date1);
    while(date_2==0){
        printf("Enter the end date (format DD:MM:YYYY):\n");
        scanf("%10s", date2);
        date_2+= validate_date_format(date2);
        date_2+= validate_date(date2);
        if(date_2==2){
            struct tm aux= transform_char_to_tm(date2);
            if(validate_second_date(info, aux))
                date_2++;
        }
        if(date_2!=3){
            printf("Invalid date!\n");
            date_2=0;
        }
    }

    char cod_banca[5], cod_tara[3];
    strncpy(cod_banca, iban+4, 4);
    cod_banca[4]='\0';
    strncpy(cod_tara, iban, 2);
    cod_tara[2]='\0';

    char buffer1[50], buffer2[50];

    if(strcmp(cod_banca, "ALMO")==0 && strcmp(cod_tara, "RO")==0){
        char cod_client[17], cod_cont[3];
        strncpy(cod_client, iban+8, 17);
        cod_cont[2]='\0';
        strncpy(cod_cont, iban+2, 2);
        cod_client[16]='\0';
        if(check_id_account(head, cod_cont)!=1){
            char path[100];
            sprintf(path, "./%s/transactions.txt", global_user);
            FILE *file1 = fopen(path, "r");
            if(file1==NULL){
                printf("Error opening file at %s\n", "users.txt");
                return;
            }

            sprintf(path, "statement-%s.txt", buffer1);
            FILE *file2 = fopen(path, "w");
            fclose(file2);
            file2 = fopen(path, "w");
            if(file2==NULL){
                printf("Error opening file at %s\n", "users.txt");
                return;
            }

            char buffer[100], type[15], sum[15], date[15], time[10], iban2[25], copy[100];
            struct tm end_date= transform_char_to_tm(date2);
            strftime(buffer1,50,"%d:%m:%Y", &info);
            strftime(buffer2,50,"%d:%m:%Y", &end_date);
            sprintf(copy, "Transaction register generated for interval: %s to %s\n"
                          "For account: %s\n", buffer1, buffer2, iban);
            fwrite(copy, 1, strlen(copy), file2);
            float expenses=0, income=0;
            while(fgets(buffer, 100, file1)){
                strcpy(copy, buffer);
                strcpy(type, strtok(buffer, ","));
                strcpy(sum, strtok(NULL, ","));
                strcpy(date, strtok(NULL, ","));
                strcpy(time, strtok(NULL, ","));
                strcpy(iban2, strtok(NULL, ",\n"));
                struct tm t_time= transform_char_to_tm(date);
                if(strcmp(iban2, iban)==0){
                    if(check_date_in_interval(end_date, info, t_time)) {
                        fwrite(copy, 1, strlen(copy), file2);
                        if(sum[0]=='+'){
                            income+=atof(sum+1);
                        }
                        else{
                            expenses+=atof(sum+1);
                        }
                    }
                }
            }
            sprintf(copy, "Expenses: %0.2f, Income: %0.2f\n", expenses, income);
            fwrite(copy, 1, strlen(copy), file2);
            fclose(file1);
            fclose(file2);
            printf("Account statement generated!\n");

            sprintf(path, "./%s/log.txt", global_user);
            file1 = fopen(path, "a");
            if(file1==NULL){
                printf("Error opening file at %s\n", "users.txt");
                return;
            }

            time_t t1;
            sprintf(copy, "Generated account statement for account with iban: %s at %s", iban, ctime(&t1));
            fwrite(copy, 1, strlen(copy), file1);
            fclose(file1);
        }
        else{
            printf("Invalid iban!\n");
        }
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
    if(strcmp(global_user, "exit")==0){
        return 0;
    }
    customers_head=load_customers(customers_head, global_user);
    accounts_head=load_accounts(accounts_head, global_user);
    menu_text();
    while(strcmp(menu_choice, "exit")!=0){
        scanf("%100s", menu_choice);
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