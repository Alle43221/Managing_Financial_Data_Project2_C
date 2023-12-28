#include "dynamic_customers.h"
#include <stdio.h>
#include <string.h>

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