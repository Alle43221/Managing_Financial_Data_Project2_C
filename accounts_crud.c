#include "accounts_crud.h"

void add_account(struct Node_account *head, char global_user[]) {
    char id_string[10]="", type[2]="";
    int type1=0, id1=0;

    while (id1==0){
        printf("Enter account id:\n");
        scanf("%10s", id_string);
        id1= validare_id(id_string);
        id1+= check_id_account(head, id_string);
        if(id1!=2){
            printf("Invalid/Existing id!\n");
        }
    }

    while (type1==0){
        printf("Enter account type: savings/checking/credit [1/2/3]\n");
        scanf("%10s", type);
        if(strcmp(type, "1")!=0 && strcmp(type, "2")!=0 && strcmp(type, "3")!=0){
            printf("Invalid type!\n");
        }
    }

    char path[100];
    sprintf(path, "./%s/log.txt",global_user);

    FILE *file1=fopen(path, "a");
    time_t t;
    time(&t);
    char str[100];
    sprintf(str, "Created account with id %s at %s",id_string,ctime(&t));
    fwrite(str, 1, strlen(str), file1);
    fclose(file1);

    sprintf(path, "./%s/accounts.txt",global_user);
    FILE *file=fopen(path, "a");
    sprintf(str, "%s,%s,%s,%s,%s\n",id_string,);
    fwrite(str, 1, strlen(str), file);
    fclose(file);
    printf("Customer added with success!\n");
}