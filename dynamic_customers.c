#include "dynamic_customers.h"

int check_id_customer(struct Node_customer* head, char new_id[]){
    /**
    * param: struct Node_customer*, char[]
    * description: checks the existence of an object with the given id in the list starting at address head
    * return: int
    * exceptions: array contains object with given id -> return 0
    */
    struct Node_customer* iterator=head;
    while(iterator!=NULL){
        if(strcmp(iterator->data.id_string,new_id)==0){
            return 0;
        }
        iterator=iterator->next;
    }
    return 1;
}

struct Node_customer* insert_at_end_customer(struct Node_customer* head, char name[], char iban[], char phone[], char id[], char email[]){
    /**
    * param: struct Node_customer*, char[], char[], char[], char[], char[]
    * description: inserts a new customer with given data at the end of the list starting at address head
    * return: struct Node_customer* (current address of head)
    * exceptions: Error allocating memory for new customer -> Memory not allocated! + program end
    */
    struct Node_customer* iterator=head;
    if(iterator==NULL){  //cazul in care este primul nod
        struct Node_customer* new_node= (struct Node_customer*) malloc(sizeof(struct Node_customer));
        if(new_node==NULL){
            printf("Memory not allocated!\n");
            exit(0);
        }
        new_node->next=NULL;
        strcpy(new_node->data.id_string, id);
        strcpy(new_node->data.phone, phone);
        strcpy(new_node->data.iban, iban);
        strcpy(new_node->data.name, name);
        strcpy(new_node->data.email, email);
        return new_node;
    }
    else
    {
        while(iterator->next!=NULL){
            iterator=iterator->next;
        }
        struct Node_customer* new_node= (struct Node_customer*) malloc(sizeof(struct Node_customer));
        if(new_node==NULL){
            printf("Memory not allocated!\n");
            exit(0);
        }
        new_node->next=NULL;
        strcpy(new_node->data.id_string, id);
        strcpy(new_node->data.phone, phone);
        strcpy(new_node->data.iban, iban);
        strcpy(new_node->data.name, name);
        strcpy(new_node->data.email, email);
        iterator->next=new_node;
        return head;
    }
}

void modify_by_id_customer(struct Node_customer* head, char id[], char name[], char iban[], char phone[], char email[]){
    /**
    * param: struct Node_customer*, char[], char[], char[], char[], char[]
    * description: modifies a customer with a given id and data in the dynamically allocated list
    * return: void
    */
    struct Node_customer* iterator=head;
    while(iterator!=NULL){
        if(strcmp(iterator->data.id_string,id)==0){
            strcpy(iterator->data.phone, phone);
            strcpy(iterator->data.iban, iban);
            strcpy(iterator->data.name, name);
            strcpy(iterator->data.email, email);
            return;
        }
        iterator=iterator->next;
    }
}

struct Node_customer* delete_by_id_customer(struct Node_customer* head, char id[]){
    /**
    * param: struct Node_customer*, char[]
    * description: deletes a customer with a given id and data from the dynamically allocated list
    * return: struct Node_customer* (current start of list)
    */
    struct Node_customer* iterator=head;
    if(strcmp(iterator->data.id_string, id)==0){
        head=iterator->next;
        free(iterator);
        return head;
    }
    while(iterator!=NULL){
        if(strcmp(iterator->next->data.id_string, id)==0){
            struct Node_customer* copy=iterator->next;
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