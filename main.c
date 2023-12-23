#include <stdio.h>
#include <string.h>
#include "time.h"
#include <ctype.h>

char global_user[50]="";

void login_menu()
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
    printf("| 1. Add customer                           |\n");
    printf("---------------------------------------------\n");
}

int validare_string(char x[]){
    /**
    * param: char[]
    * description: validates an array of characters
    * return: int
    * exceptions: array contains spaces -> return 0
    *             array contains commas -> return 0
    *             array contains digits -> return 0
    */
    if (strlen(x)==0)
        return 0;
    int len=strlen(x);
    char digits[]="0123456789";
    for(int i=0; i<len; i++){
        if(x[i]==' ')
            return 0;
        else if(strchr(digits, x[i]))
            return 0;
        else if(x[i]==',')
            return 0;
    }
    return 1;
}

int validare_iban(char x[]){
    /**
    * param: char[]
    * description: validates an iban code
    * return: int
    * exceptions: code doesn't comply with the format "AB49ABCD1B31007593840000"
     *  first two characters -> letters
     *  next two characters -> digits
     *  next four characters -> letters
     *  remaining characters -> alphanumeric characters
     *  total of 24 characters
    */
    if (strlen(x)!=24)
        return 0;
    if(!isalpha(x[0])|| !isalpha(x[1]))
        return 0;
    if(!isdigit(x[2])|| !isdigit(x[3]))
        return 0;
    if(!isalpha(x[4])|| !isalpha(x[5])|| !isalpha(x[6])|| !isalpha((x[7])))
        return 0;

    int len=strlen(x);
    for(int i=8; i<len; i++){
        if(!isdigit(x[i])&&!isalpha(x[i]))
            return 0;
    }
    return 1;
}

int validare_phone(char x[]) {
    /**
      * param: char[]
      * description: validates a phone number
      * return: int
      * exceptions: number contains non-numeric characters
      *  total of 10 characters
      */
    int len=strlen(x);
    if(len!=10)
        return 0;
    for(int i=0; i<len; i++){
        if(!isdigit(x[i]))
            return 0;
    }
    return 1;
}

int validare_id(char x[10]) {
    /**
    * param: char[]
    * description: validates an id
    * return: int
    * exceptions: number contains non-numeric characters
    */
    int len=strlen(x);
    if(len==0)
        return 0;
    for(int i=0; i<len; i++){
        if(!isdigit(x[i]))
            return 0;
    }
    return 1;
}

int validare_email(char x[10]) {
    /**
    * param: char[]
    * description: validates an email address
    * return: int
    * exceptions: array doesn't contain the symbol "@"
    */
    int len=strlen(x);
    if(len==0)
        return 0;
    const char simbol='@';
    if(strchr(x, simbol)==NULL)
        return 0;
    return 1;
}

void add_customer(){
    char name[50]="", iban[25]="", phone[11]="", id_string[10]="", email[50]="";
    while (validare_string(name)==0){
        printf("Enter customer name:\n");
        scanf("%50s", name);
    }

    while (validare_iban(iban)==0){
        printf("Enter customer iban:\n");
        scanf("%25s", iban);
    }

    while (validare_phone(phone)==0){
        printf("Enter customer phone number:\n");
        scanf("%11s", phone);
    }

    while (validare_email(email)==0){
        printf("Enter customer email address:\n");
        scanf("%50s", email);
    }

    while (validare_id(id_string)==0){
        printf("Enter customer id:\n");
        scanf("%10s", id_string);
    }

    //verificare existenta id

    char path[100];
    sprintf(path, "./%s/log.txt",global_user);

    FILE *file1=fopen(path, "a");
    time_t t;
    time(&t);
    char str[100];
    sprintf(str, "Added customer with id %s at %s",id_string,ctime(&t));
    fwrite(str, 1, strlen(str), file1);
    fclose(file1);

    sprintf(path, "./%s/customers.txt",global_user);
    FILE *file=fopen(path, "a");
    sprintf(str, "%s,%s,%s,%s,%s",id_string,name, iban, phone, email);
    fwrite(str, 1, strlen(str), file);
    fclose(file);
    printf("Customer added with success!\n");
}

int main(){
    /**
     * param: none
     * description: console interface for transaction app
     * exception: ends the program on input "exit"
     */

    char menu_choice[100];
    welcome_text();
    while(strlen(global_user)==0){
        login_menu();
    }
    menu_text();
    while(strcmp(menu_choice, "exit")!=0){
        scanf("%100s", menu_choice);
        if(strcmp(menu_choice,"1")==0){
            add_customer();
        }
        else if(strcmp(menu_choice,"2")==0){
            add_customer();
        }
        else{
            printf("Invalid option!\n");
        }
    }
    return 0;
}