#include "admin_operations.h"

void select_user_admin(char global_user[], char user_id[]){
    /**
     * param: char[]
     * description: selects the user for which the admin will make various operations
     * return: void
     * exception: Error opening file at path
     *            Invalid username! - no user found
     */
    FILE *file=fopen("users.csv", "r");
    if(file==NULL){
        printf("Error opening file at users.csv\n");
        return;
    }
    char username[50], username1[50], buffer[100], pass[50], user[17];
    printf("Enter username:\n");
    gets(username);
    while(fgets(buffer, 100, file)) {
        strcpy(username1, strtok(buffer, ",\n"));
        strcpy(pass, strtok(NULL, ",\n"));
        strcpy(user, strtok(NULL, ",\n"));
        if (strcmp(username, username1) == 0) {
            strcpy(global_user, username);
            strcpy(user_id, user);
        }
    }
    if(strcmp(global_user, "admin")==0)
        printf("Invalid username!\n");
}

void add_user(char global_user[]){
    /**
     * param: char[]
     * description: creates a new user with a given username, id and password and all the required functions for it
     * return: void
     * exceptions: Permission denied/Error opening file at path
     */
    if(strcmp(global_user, "admin")==0){
        char username[50], string_id[17], password[30]="";
        int username1=0, id=0;
        while(username1==0){
            printf("Enter username:\n");
            gets(username);
            username1+= validare_string(username);
            username1+= check_username(username);
            if(username1!=2){
                printf("Invalid username!\n");
                username1=0;
            }
        }
        while(id==0){
            printf("Enter id:\n");
            gets(string_id);
            id+= validare_id(string_id);
            id+=check_user_id(string_id);
            if(id!=2 || strlen(string_id)!=16){
                printf("Invalid id!\n");
                id=0;
            }
        }
        while(strlen(password)<4){
            printf("Enter password:\n");
            gets(password);
            if(validate_password(password)==0){
                printf("Password must be at least 4 characters long and cannot contain spaces!\n");
            }
        }
        _mkdir(username);
        char path[100];
        sprintf(path, "./%s/log.txt",username);
        FILE *file1=fopen(path, "w");
        sprintf(path, "./%s/accounts.csv",username);
        FILE *file2=fopen(path, "w");
        sprintf(path, "./%s/customers.csv",username);
        FILE *file3=fopen(path, "w");
        sprintf(path, "./%s/transactions.csv",username);
        FILE *file4=fopen(path, "w");
        fclose(file1);
        fclose(file2);
        fclose(file3);
        fclose(file4);

        sprintf(path, "users.csv");
        FILE *file5=fopen(path, "a");
        if(file5==NULL){
            printf("Error opening file at users.csv\n");
            return;
        }
        char str[100];
        sprintf(str, "%s %s %s\n", username, password, string_id);
        fwrite(str, 1, strlen(str), file5);
        fclose(file5);
    }
    else{
        printf("Permission denied!\n");
    }
}