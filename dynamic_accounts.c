#include "dynamic_accounts.h"

int check_id_account(struct Node_account* head, char new_id[]){
    struct Node_account* iterator=head;
    char *p;
    while(iterator!=NULL){
        strncpy(p, iterator->data.iban+2, 2);
        if(strcmp(p,new_id)==0){
            return 0;
        }
        iterator=iterator->next;
    }
    return 1;
}

void insert_at_end_account(struct Node_account* head, char type[], char id[], char cod_client[]){
    struct Node_account* iterator=head;
    if(iterator==NULL){  //cazul in care este primul nod
        struct Node_account* new_node= (struct Node_account*) malloc(sizeof(struct Node_account));
        new_node->next=NULL;
        strcpy(&new_node->data.type, type);
        new_node->data.balance=0;
        char iban[25];
        strcpy(iban, "RO");
        strcpy(iban+2, id);
        strcpy(iban+4, "ALMO");
        strcpy(iban+8, cod_client);
        strcpy(new_node->data.iban, iban);
        head=new_node;
    }
    else
    {
        while(iterator->next!=NULL){
            iterator=iterator->next;
        }
        struct Node_account* new_node= (struct Node_account*) malloc(sizeof(struct Node_account));
        new_node->next=NULL;
        strcpy(&new_node->data.type, type);
        new_node->data.balance=0;
        char iban[25];
        strcpy(iban, "RO");
        strcpy(iban+2, id);
        strcpy(iban+4, "ALMO");
        strcpy(iban+8, cod_client);
        strcpy(new_node->data.iban, iban);
        iterator->next=new_node;
    }
}

int delete_by_id_account(struct Node_account* head, char id[]){
    struct Node_account* iterator=head;
    char *p;
    strncpy(p, iterator->data.iban+2, 2);
    if(strcmp(p,id)==0){
        head=iterator->next;
        free(iterator);
        return 1;
    }
    while(iterator->next!=NULL){
        strncpy(p, iterator->data.iban+2, 2);
        if(strcmp(p,id)==0){
            struct Node_account* copy=iterator->next;
            iterator->next=iterator->next->next;
            free(copy);
            return 1;
        }
        else{
            iterator=iterator->next;
        }
    }
    return 0;
}