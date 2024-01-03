#include "accounts_crud.h"

struct Node_account* add_account(struct Node_account *head, char global_user[], char id_client[]) {
    /**
    * param: struct Node_account*, char[], char[]
    * return: struct Node_account* (current address of the start of the list)
    * description: adds a new account to the list starting at head and into the .../accounts.csv file
    * exception: Error opening file at path
    */
    char id_string[10]="", type[2]="";
    int type1=0, id1=0;

    while (id1==0){
        printf("Enter account id (two digits):\n");
        gets(id_string);
        id1= validare_id(id_string);
        id1+= check_id_account(head, id_string);
        if(strlen(id_string)==2){
            id1+=1;
        }
        if(id1!=3){
            printf("Invalid/Existing id!\n");
            id1=0;
        }
    }

    while (type1==0){
        printf("Enter account type: savings/checking/credit [1/2/3]\n");
        gets(type);
        if(strcmp(type, "1")!=0 && strcmp(type, "2")!=0 && strcmp(type, "3")!=0){
            printf("Invalid type!\n");
        }
        else type1=1;
    }
    char iban[25];
    strcpy(iban, "RO");
    strcpy(iban+2, id_string);
    strcpy(iban+4, "ALMO");
    strcpy(iban+8, id_client);

    head=insert_at_end_account(head, type, iban, 0.0f);

    char path[100];
    sprintf(path, "./%s/log.txt",global_user);

    FILE *file1=fopen(path, "a");
    if(file1==NULL){
        printf("Error opening file at %s\n", path);
        return head;
    }
    time_t t;
    time(&t);
    char str[100];
    sprintf(str, "Created account with iban %s at %s",iban,ctime(&t));
    fwrite(str, 1, strlen(str), file1);
    fclose(file1);

    sprintf(path, "./%s/accounts.csv",global_user);
    FILE *file=fopen(path, "a");
    if(file==NULL){
        printf("Error opening file at %s\n", path);
        return head;
    }
    sprintf(str, "%s,%s,0\n",iban, type);
    fwrite(str, 1, strlen(str), file);
    fclose(file);
    printf("Account created with success!\n");
    return head;
}

struct Node_account * load_accounts(struct Node_account *head, char global_user[]){
    /**
     * param: struct Node_account*, char[]
     * return: struct Node_account* (current address of the start of the list)
     * description: loads all the accounts in dynamically allocated list starting at address head from file .../customers.csv
     * exception: Error opening file at path
     */
    char path[100], str[100];
    sprintf(path, "./%s/accounts.csv",global_user);
    FILE *file=fopen(path, "r");
    if(file==NULL){
        printf("Error opening file at %s\n", path);
        return head;
    }
    while(fgets(str, 100, file)){
        char *iban= strtok(str, ",\n");
        char *type=strtok(NULL, ",\n");
        float value=atof(strtok(NULL, ",\n"));
        head=insert_at_end_account(head, type, iban, value);
    }
    fclose(file);
    return head;
}

void print_all_accounts(struct Node_account *head) {
    /**
     * param: struct Node_account*
     * return: void
     * description: prints all the accounts from the dynamically allocated list starting at address head
     * exception: No accounts available
     */
    struct Node_account* iterator=head;
    char types[][10]={"0", "savings", "checking", "credit"};
    if(head==NULL)
        printf("No accounts available!\n");
    else
    while(iterator!=NULL){

        printf("%s %s %0.2f\n", iterator->data.iban, types[iterator->data.type-'0'], iterator->data.balance);
        iterator=iterator->next;
    }
}

void save_accounts_to_file(struct Node_account *head, char global_user[]){
    /**
     * param: struct Node_account*, char[]
     * return: void
     * description: saves all the accounts in dynamically allocated list starting at address head to file .../accounts.csv
     * exception: Error opening file at path
     */
    char path[100];
    sprintf(path, "./%s/accounts.csv",global_user);
    FILE *file1=fopen(path, "w");
    if(file1==NULL){
        printf("Error opening file at %s\n", path);
        return;
    }
    struct Node_account* iterator=head;
    while(iterator!=NULL){
        char str[100];
        sprintf(str, "%s,%s,%0.2f\n", iterator->data.iban, &iterator->data.type, iterator->data.balance);
        fwrite(str, 1, strlen(str), file1);
        iterator=iterator->next;
    }
    fclose(file1);
}

struct Node_account * delete_account(struct Node_account *head, char global_user[]) {
    /**
   * param: struct Node_account*, char[]
   * return: struct Node_account* (current starting address for list)
   * description: deletes an account identified by id from the list starting at head and from the .../accounts.csv file
   * exception: Error opening file at path
    *           Account not found
     *          Non-zero balance for selected account!
   */
    int id1=0;
    char id_string[10]="";
    while (id1==0){
        printf("Enter account id:\n");
        gets(id_string);
        id1= validare_id(id_string);
        if(id1!=1){
            printf("Invalid id!\n");
        }
    }
    int rez= check_id_account(head, id_string);

    head=delete_by_id_account(head, id_string);
    if(rez==0){
        printf("Account deleted with success!\n");
        char path[100];
        sprintf(path, "./%s/log.txt",global_user);

        FILE *file1=fopen(path, "a");
        if(file1==NULL){
            printf("Error opening file at %s\n", path);
            return head;
        }
        time_t t;
        time(&t);
        char str[100];
        sprintf(str, "Deleted customer with id %s at %s",id_string,ctime(&t));
        fwrite(str, 1, strlen(str), file1);

        save_accounts_to_file(head, global_user);
        fclose(file1);
    }
    else if(rez==1)
        printf("Account not found!\n");
    else
        printf("Non-empty balance for selected account! Please transfer the sum!\n");
    return head;
}

void check_account_balance(struct Node_account *head){
    /**
    * param: struct Node_customer*
    * return: void
    * description: prints the balance of the selected account from the list starting at address head
    */
    char id_string[10]="";
    int id1=10;

    while (id1==10){
        printf("Enter account id:\n");
        gets(id_string);
        id1= validare_id(id_string);
        id1+= check_id_account(head, id_string);
        if(id1!=2){
            printf("Invalid/Non-existing id!\n");
            id1=10;
        }
    }
    struct Node_account* iterator=head;
    char p[3];
    while(iterator!=NULL){
        strncpy(p, iterator->data.iban+2, 2);
        if(strcmp(p,id_string)==0){
            printf("Account balance: %0.2f\n", iterator->data.balance);
            return;
        }
        iterator=iterator->next;
    }

}
