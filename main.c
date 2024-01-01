#include <stdio.h>
#include <string.h>
#include "time.h"
#include <ctype.h>
#include "customers_crud.h"
#include "accounts_crud.h"
#include "math.h"

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
    printf("---------------------------------------------\n");
    printf("| 8. Save deposit                           |\n");
    printf("| 9. Save withdrawal                        |\n");
    printf("| 10. Save transaction                      |\n");
    printf("---------------------------------------------\n");
    printf("| 11. Log out                               |\n");
    printf("---------------------------------------------\n");
}

int validate_amount(char s[]){
    /**
    * param: char[]
    * return: integer (0/1)
    * description: checks if the string provided corresponds to a valid amount
    */
    int len=strlen(s);
    for(int i=0; i< len; i++){
        if(isdigit(s[i])==0 && s[i]!='.')
            return 0;
    }
    double amount=atof(s);
    if(amount<=0)
        return 0;
    if(amount>10000000)
        return 0;
    amount*=100.0;
    float epsilon=0.0000000001;
    if(abs(amount- (int) amount)>epsilon)
        return 0;
    return 1;
}

void save_deposit(struct Node_account* head, char global_user[]){
    char value_string[10], iban[25];
    float value;
    int iban1=0, value1=0;
    while(iban1==0){
        printf("Enter the account iban:\n");
        scanf("%25s", iban);
        iban1+=validare_iban(iban);
        if(iban1==0){
            printf("Invalid iban!\n");
        }
    }

    while(value1==0){
        printf("Enter the amount:\n");
        scanf("%10s", value_string);
        value1+= validate_amount(value_string);
        if(value1==0){
            printf("Invalid value!\n");
        }
    }
    value=atof(value_string);
    value=value*100;
    value=roundf(value);
    value/=100;

    char cod_banca[5], cod_tara[3];
    strncpy(cod_banca, iban+4, 4);
    strncpy(cod_tara, iban, 2);
    cod_tara[2]='\0';
    if(strcmp(cod_banca, "ALMO")==0 && strcmp(cod_tara, "RO")==0){
        char cod_client[17], cod_cont[3];
        strncpy(cod_client, iban+8, 17);
        strncpy(cod_cont, iban+2, 2);

        char username[50], password[50], buffer[100], user_id[17];
        FILE *file=fopen("users.txt", "r");
        int gasit=0;
        while(fgets(buffer, 100, file)) {
            strcpy(username, strtok(buffer, " \n"));
            strcpy(password, strtok(NULL, " \n"));
            strcpy(user_id, strtok(NULL, " \n"));
            if (strcmp(user_id, cod_client)==0){
                gasit=1;

                char path[100];
                sprintf(path, "./%s/log.txt",username);
                FILE *file1=fopen(path, "a");
                time_t t;
                time(&t);
                char str[100];
                sprintf(str, "Deposited %0.2f in account with iban %s at %s",value, iban,ctime(&t));
                fwrite(str, 1, strlen(str), file1);
                fclose(file1);

                modify_account_by_id(head, cod_cont, value);
                save_accounts_to_file(head, username);
            }
        }
        if(gasit==0){
            printf("Invalid iban!\n");
        }
        fclose(file);
    }
    else{
        char path[100];
        sprintf(path, "./%s/log.txt", global_user);
        FILE *file1=fopen(path, "a");
        time_t t;
        time(&t);
        char str[100];
        sprintf(str, "Deposited %0.2f in account with iban %s at %s",value, iban,ctime(&t));
        fwrite(str, 1, strlen(str), file1);
        fclose(file1);
    }
    printf("Successful deposit!\n");
}

void save_withdrawal(struct Node_account *head, char user_id[], char  global_user[]) {
    char value_string[10], iban[25];
    float value;
    int iban1=0, value1=0;
    while(iban1==0){
        printf("Enter the account iban:\n");
        scanf("%25s", iban);
        iban1+=validare_iban(iban);
        if(iban1==0){
            printf("Invalid iban!\n");
        }
    }

    while(value1==0){
        printf("Enter the amount:\n");
        scanf("%10s", value_string);
        value1+= validate_amount(value_string);
        if(value1==0){
            printf("Invalid value!\n");
        }
    }
    value=atof(value_string);
    value=value*100;
    value=roundf(value);
    value/=100;

    char cod_banca[5], cod_tara[3];
    strncpy(cod_banca, iban+4, 4);
    strncpy(cod_tara, iban, 2);
    cod_tara[2]='\0';
    if(strcmp(cod_banca, "ALMO")==0 && strcmp(cod_tara, "RO")==0){
        char cod_client[17], cod_cont[3];
        strncpy(cod_client, iban+8, 17);
        strncpy(cod_cont, iban+2, 2);
        if (strcmp(user_id, cod_client)==0) {
            char path[100];
            sprintf(path, "./%s/log.txt", global_user);
            FILE *file1 = fopen(path, "a");
            time_t t;
            time(&t);
            char str[100];
            sprintf(str, "Withdraw %0.2f from account with iban %s at %s", value, iban, ctime(&t));
            fwrite(str, 1, strlen(str), file1);
            fclose(file1);

            sprintf(path, "./%s/transactions.txt", global_user);
            FILE *file2 = fopen(path, "a");
            time_t t1;
            struct tm* info = localtime( &t1 );
            char buffer[50];
            strftime(buffer,50,"%d:%m:%Y,%H:%M:%S", info);
            sprintf(str, "withdrawal,-%0.2f,%s,%s\n", value,  buffer,iban);
            fwrite(str, 1, strlen(str), file2);
            fclose(file2);

            modify_account_by_id(head, cod_cont, value*(-1.0));
            save_accounts_to_file(head, global_user);
            printf("Successful withdrawal!\n");
        }
        else {
            printf("Permission denied/Invalid iban!\n");
        }
    }
}

void save_transfer(struct Node_account* head, char user_id[], char global_user[]) {
    char value_string[10], iban[25], iban2[25];
    float value;
    int iban1 = 0, value1 = 0;
    while (iban1 == 0) {
        printf("Enter the source account iban:\n");
        scanf("%25s", iban);
        iban1 += validare_iban(iban);
        if (iban1 == 0) {
            printf("Invalid iban!\n");
        }
    }

    iban1 = 0;
    while (iban1 == 0) {
        printf("Enter the destination account iban:\n");
        scanf("%25s", iban2);
        iban1 += validare_iban(iban2);
        if (iban1 == 0) {
            printf("Invalid iban!\n");
        }
    }

    while (value1 == 0) {
        printf("Enter the amount:\n");
        scanf("%10s", value_string);
        value1 += validate_amount(value_string);
        if (value1 == 0) {
            printf("Invalid value!\n");
        }
    }
    value = atof(value_string);
    value = value * 100;
    value = roundf(value);
    value /= 100;

    char cod_banca[5], cod_tara[3];
    strncpy(cod_banca, iban + 4, 4);
    cod_banca[4] = '\0';
    strncpy(cod_tara, iban, 2);
    cod_tara[2] = '\0';

    char cod_banca2[5], cod_tara2[3];
    strncpy(cod_banca2, iban2 + 4, 4);
    cod_banca2[4] = '\0';
    strncpy(cod_tara2, iban2, 2);
    cod_tara2[2] = '\0';

    char cod_client[17], cod_cont[3];
    strncpy(cod_client, iban + 8, 17);
    strncpy(cod_cont, iban + 2, 2);

    char cod_client_destination[17], cod_cont_destination[3];
    strncpy(cod_client_destination, iban2 + 8, 17);
    strncpy(cod_cont_destination, iban2 + 2, 2);

    if (strcmp(cod_banca, "ALMO") == 0 && strcmp(cod_tara, "RO") == 0) {
        if (strcmp(cod_client, user_id) == 0) {
            time_t t1 = time(0);
            struct tm *info = localtime( &t1 );
            char buffer1[50];
            strftime(buffer1,50,"%d:%m:%Y,%H:%M:%S", info);

            if (strcmp(cod_banca2, "ALMO") == 0 && strcmp(cod_tara2, "RO") == 0) {

                char username[50], password[50], buffer[100], user_id_destination[17];
                FILE *file = fopen("users.txt", "r");
                int gasit = 0;
                while (fgets(buffer, 100, file)) {
                    strcpy(username, strtok(buffer, " \n"));
                    strcpy(password, strtok(NULL, " \n"));
                    strcpy(user_id_destination, strtok(NULL, " \n"));
                    if (strcmp(user_id_destination, cod_client_destination) == 0) {
                        gasit = 1;

                        char path[100];
                        sprintf(path, "./%s/log.txt", username);
                        FILE *file1 = fopen(path, "a");
                        time_t t;
                        time(&t);
                        char str[100];
                        sprintf(str, "Received %0.2f from account with iban %s in account with iban %s at %s", value, iban, iban2, ctime(&t));
                        fwrite(str, 1, strlen(str), file1);
                        fclose(file1);

                        sprintf(path, "./%s/transactions.txt", username);
                        FILE *file2 = fopen(path, "a");
                        strftime(buffer1,50,"%d:%m:%Y,%H:%M:%S", info);
                        sprintf(str, "transfer,+%0.2f,%s,%s,%s\n", value, buffer1,iban2, iban);
                        fwrite(str, 1, strlen(str), file2);
                        fclose(file2);

                        struct Node_account *head1=NULL;
                        head1=load_accounts(head1, username);
                        modify_account_by_id(head1, cod_cont_destination, value);
                        save_accounts_to_file(head1, username);
                    }
                }
                fclose(file);
                if (gasit == 0) {
                    printf("Invalid iban!\n");
                    return;
                }
            }
            modify_account_by_id(head, cod_cont, value*(-1.0f));
            save_accounts_to_file(head, global_user);

            char path[100];
            sprintf(path, "./%s/log.txt", global_user);
            FILE *file1 = fopen(path, "a");
            time_t t;
            time(&t);
            char str[100];
            sprintf(str, "Transferred %0.2f from account with iban %s in account with iban %s at %s", value, iban, iban2, ctime(&t));
            fwrite(str, 1, strlen(str), file1);
            fclose(file1);

            sprintf(path, "./%s/transactions.txt", global_user);
            FILE *file2 = fopen(path, "a");

            sprintf(str, "transfer,-%0.2f,%s,%s,%s\n", value, buffer1,iban, iban2);
            fwrite(str, 1, strlen(str), file2);
            fclose(file2);

            printf("Successful transaction!\n");
        }
        else{
            printf("Permission denied!\n");
        }
    } else {
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
            save_deposit(accounts_head, global_user);
        }
        else if(strcmp(menu_choice,"9")==0){
            save_withdrawal(accounts_head, user_id, global_user);
        }
        else if(strcmp(menu_choice,"10")==0){
            save_transfer(accounts_head, user_id, global_user);
        }
        else if(strcmp(menu_choice,"11")==0){
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
        else if(strcmp(menu_choice,"exit")==0){
            return 0;
        }
        else{
            printf("Invalid option!\n");
        }
    }
    return 0;
}