#include <stdio.h>
#include <string.h>
#include "time.h"

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
    scanf("%250s", username);
    printf("Enter password:\n");
    scanf("%250s", password);
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
                sprintf(str, "Login at %s\n",ctime(&t));
                fwrite(str, 1, sizeof(str), file1);
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

        }
        else{
            printf("Invalid option!\n");
        }
    }
    return 0;
}