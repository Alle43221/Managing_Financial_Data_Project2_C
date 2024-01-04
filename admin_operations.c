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

struct Node_user* add_user(struct Node_user* head){
    /**
     * param: char[]
     * description: creates a new user with a given username, id and password and all the required functions for it
     * return: void
     * exceptions: Error opening file at path
     */
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

    printf("User created with success!\n");

    sprintf(path, "users.csv");
    FILE *file5=fopen(path, "a");
    if(file5==NULL){
        printf("Error opening file at users.csv\n");
        return head;
    }
    char str[100];
    sprintf(str, "%s,%s,%s\n", username, password, string_id);
    fwrite(str, 1, strlen(str), file5);
    fclose(file5);

    sprintf(path, "./admin/log.txt");
    FILE *file=fopen(path, "a");
    if(file==NULL){
        printf("Error opening file at %s\n", path);
        return head;
    }
    time_t t;
    time(&t);
    sprintf(str, "Created user with id %s at %s",string_id,ctime(&t));
    fwrite(str, 1, strlen(str), file);
    fclose(file);

    return insert_at_end_user(head, string_id, username, password);
}

struct Node_user* load_users(struct Node_user *head){
    /**
     * param: struct Node_user*
     * return: struct Node_user* (current address of the start of the list)
     * description: loads all the users in dynamically allocated list starting at address head from file users.csv
     * exception: Error opening file at path
     */
    char path[100], str[100];
    sprintf(path, "users.csv");
    FILE *file=fopen(path, "r");
    if(file==NULL){
        printf("Error opening file at %s\n", path);
        return head;
    }
    while(fgets(str, 100, file)){
        char *username= strtok(str, ",\n");
        char *password=strtok(NULL, ",\n");
        char *id=strtok(NULL, ",\n");
        head=insert_at_end_user(head, id, username, password);
    }
    fclose(file);
    return head;
}

void save_users_to_file(struct Node_user *head){
    /**
     * param: struct Node_user*
     * return: void
     * description: saves all the users in dynamically allocated list starting at address head to file users.csv
     * exception: Error opening file at path
     */
    char path[100];
    sprintf(path, "users.csv");
    FILE *file1=fopen(path, "w");
    if(file1==NULL){
        printf("Error opening file at %s\n", path);
        return;
    }
    struct Node_user* iterator=head;
    while(iterator!=NULL){
        char str[100];
        sprintf(str, "%s,%s,%s\n", iterator->data.username, iterator->data.password, iterator->data.id);
        fwrite(str, 1, strlen(str), file1);
        iterator=iterator->next;
    }
    fclose(file1);
}

struct Node_user * delete_user(struct Node_user *head) {
    /**
   * param: struct Node_user*
   * return: struct Node_user* (current starting address for list)
   * description: deletes a user identified by id from the list starting at head and from the users.csv file
   * exception: Error opening file at path
    *           User not found
   */
    int id1=0;
    char id_string[17]="";
    while (id1==0){
        printf("Enter user id:\n");
        gets(id_string);
        id1= validare_id(id_string);
        if(id1!=1 || strlen(id_string)!=16){
            printf("Invalid id!\n");
        }
    }
    int rez= check_user_id(id_string);

    if(rez==0){
        head=delete_by_id_user(head, id_string);
        printf("User deleted with success!\n");
        char path[100];
        sprintf(path, "./admin/log.txt");

        FILE *file1=fopen(path, "a");
        if(file1==NULL){
            printf("Error opening file at %s\n", path);
            return head;
        }
        time_t t;
        time(&t);
        char str[100];
        sprintf(str, "Deleted user with id %s at %s",id_string,ctime(&t));
        fwrite(str, 1, strlen(str), file1);
        fclose(file1);
    }
    else
        printf("User not found!\n");
    return head;
}

struct Node_user * reset_password(struct Node_user *head) {
    /**
   * param: struct Node_user*
   * return: struct Node_user* (current starting address for list)
   * description: deletes a user identified by id from the list starting at head and from the users.csv file
   * exception: Error opening file at path
    *           User not found
   */

    int id1=0;
    char id_string[17]="", password[30];
    while (id1==0){
        printf("Enter user id:\n");
        gets(id_string);
        id1= validare_id(id_string);
        if(id1!=1 || strlen(id_string)!=16){
            printf("Invalid id!\n");
        }
    }
    while(strlen(password)<4){
        printf("Enter new password:\n");
        gets(password);
        if(validate_password(password)==0){
            printf("Password must be at least 4 characters long and cannot contain spaces!\n");
        }
    }
    int rez= check_user_id(id_string);

    if(rez==0){
        modify_user_by_id(head, id_string, password);
        printf("Password changed with success!\n");
        char path[100];
        sprintf(path, "./admin/log.txt");

        FILE *file1=fopen(path, "a");
        if(file1==NULL){
            printf("Error opening file at %s\n", path);
            return head;
        }
        time_t t;
        time(&t);
        char str[100];
        sprintf(str, "Changed password for user with id %s at %s",id_string,ctime(&t));
        fwrite(str, 1, strlen(str), file1);
        fclose(file1);
    }
    else
        printf("User not found!\n");

}