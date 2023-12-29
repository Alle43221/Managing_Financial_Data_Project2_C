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

void insert_at_end_customer(struct Node_customer* head, char name[], char iban[], char phone[], char id[], char email[]){
    struct Node_customer* iterator=head;
    if(iterator==NULL){  //cazul in care este primul nod
        struct Node_customer* new_node= (struct Node_customer*) malloc(sizeof(struct Node_customer));
        new_node->next=NULL;
        strcpy(new_node->data.id_string, id);
        strcpy(new_node->data.iban, iban);
        head=new_node;
    }
    else
    {
        while(iterator->next!=NULL){
            iterator=iterator->next;
        }
        struct Node_customer* new_node= (struct Node_customer*) malloc(sizeof(struct Node_customer));
        new_node->next=NULL;
        strcpy(new_node->data.id_string, id);
        strcpy(new_node->data.iban, iban);
        iterator->next=new_node;
    }
}

int delete_by_id_customer(struct Node_customer* head, char id[]){
    struct Node_customer* iterator=head;
    if(strcmp(iterator->data.id_string, id)==0){
        head=iterator->next;
        free(iterator);
        return 1;
    }
    while(iterator->next!=NULL){
        if(strcmp(iterator->next->data.id_string, id)==0){
            struct Node_customer* copy=iterator->next;
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