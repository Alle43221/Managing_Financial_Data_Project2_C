#include "dynamic_accounts.h"

int check_id_account(struct Node_account* head, char new_id[]){
    /**
    * param: struct Node_accounts*, char[]
    * description: checks the existence of an object with the given id in the list starting at address head
    * return: int
    * exceptions: array contains object with given id -> return 0
     *            array contains account with balance zero -> return -1
    */
    struct Node_account* iterator=head;
    char p[3];
    while(iterator!=NULL){
        strncpy(p, iterator->data.iban+2, 2);
        if(strcmp(p,new_id)==0){
            if(iterator->data.balance!=0.0f)
                return -1;
            return 0;
        }
        iterator=iterator->next;
    }
    return 1;
}

struct Node_account* insert_at_end_account(struct Node_account* head, char type[], char iban[], float value){
    /**
    * param: struct Node_customer*, char[], char[], float
    * description: inserts a new account with given data at the end of the list starting at address head
    * return: struct Node_account* (current address of head)
    * exceptions: Error allocating memory for new account -> Memory not allocated! + program end
    */
    struct Node_account* iterator=head;
    if(iterator==NULL){  //cazul in care este primul nod
        struct Node_account* new_node= (struct Node_account*) malloc(sizeof(struct Node_account));
        if(new_node==NULL){
            printf("Memory not allocated!\n");
            exit(0);
        }
        new_node->next=NULL;
        strcpy(&new_node->data.type, type);
        new_node->data.balance=value;
        strcpy(new_node->data.iban, iban);
        head=new_node;
    }
    else
    {
        while(iterator->next!=NULL){
            iterator=iterator->next;
        }
        struct Node_account* new_node= (struct Node_account*) malloc(sizeof(struct Node_account));
        if(new_node==NULL){
            printf("Memory not allocated!\n");
            exit(0);
        }
        new_node->next=NULL;
        strcpy(&new_node->data.type, type);
        new_node->data.balance=0;
        strcpy(new_node->data.iban, iban);
        iterator->next=new_node;
    }
    return head;
}

struct Node_account* delete_by_id_account(struct Node_account* head, char id[]){
    /**
    * param: struct Node_account*, char[]
    * description: deletes an account with a given id and data from the dynamically allocated list
    * return: struct Node_account* (current start of list)
    */
    struct Node_account* iterator=head;
    char p[3];
    strncpy(p, iterator->data.iban+2, 2);
    if(strcmp(p,id)==0){
        head=iterator->next;
        free(iterator);
        return head;
    }
    while(iterator!=NULL){
        strncpy(p, iterator->data.iban+2, 2);
        if(strcmp(p,id)==0){
            struct Node_account* copy=iterator->next;
            if(iterator->next!=NULL)
                iterator->next=iterator->next->next;
            free(copy);
            return head;
        }
        else{
            iterator=iterator->next;
        }
    }
    return head;
}

void modify_account_by_id(struct Node_account *head, char id_string[], float value) {
    /**
    * param: struct Node_account*, char[], float
    * description: modifies an account with a given id and data in the dynamically allocated list
    * return: void
    */
    struct Node_account* iterator=head;
    char p[3];
    while(iterator!=NULL){
        strncpy(p, iterator->data.iban+2, 2);
        p[2]='\0';
        if(strcmp(p,id_string)==0){
            float nearest = roundf(value * 100) / 100;
            iterator->data.balance+=nearest;
            return;
        }
        iterator=iterator->next;
    }
}