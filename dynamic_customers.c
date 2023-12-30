#include "dynamic_customers.h"

int check_id_customer(struct Node_customer* head, char new_id[]){
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
    struct Node_customer* iterator=head;
    if(iterator==NULL){  //cazul in care este primul nod
        struct Node_customer* new_node= (struct Node_customer*) malloc(sizeof(struct Node_customer));
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
    struct Node_customer* iterator=head;
    if(strcmp(iterator->data.id_string, id)==0){
        head=iterator->next;
        free(iterator);
        return head;
    }
    while(iterator->next!=NULL){
        if(strcmp(iterator->next->data.id_string, id)==0){
            struct Node_customer* copy=iterator->next;
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