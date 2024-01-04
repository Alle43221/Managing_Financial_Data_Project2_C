#include "dynamic_users.h"

struct Node_user* insert_at_end_user(struct Node_user* head, char id[], char username[], char password[]){
    /**
    * param: struct Node_user*, char[], char[], char[]
    * description: inserts a new user with given data at the end of the list starting at address head
    * return: struct Node_user* (current address of head)
    * exceptions: Error allocating memory for new user -> Memory not allocated! + program end
    */
    struct Node_user* iterator=head;
    if(iterator==NULL){  //cazul in care este primul nod
        struct Node_user* new_node= (struct Node_user*) malloc(sizeof(struct Node_user));
        if(new_node==NULL){
            printf("Memory not allocated!\n");
            exit(0);
        }
        new_node->next=NULL;
        strcpy(new_node->data.id, id);
        strcpy(new_node->data.username, username);
        strcpy(new_node->data.password, password);
        head=new_node;
    }
    else
    {
        while(iterator->next!=NULL){
            iterator=iterator->next;
        }
        struct Node_user* new_node= (struct Node_user*) malloc(sizeof(struct Node_user));
        if(new_node==NULL){
            printf("Memory not allocated!\n");
            exit(0);
        }
        new_node->next=NULL;
        strcpy(new_node->data.id, id);
        strcpy(new_node->data.username, username);
        strcpy(new_node->data.password, password);
        iterator->next=new_node;
    }
    return head;
}

struct Node_user* delete_by_id_user(struct Node_user* head, char id[]){
    /**
    * param: struct Node_user*, char[]
    * description: deletes a user with a given id and data from the dynamically allocated list
    * return: struct Node_user* (current start of list)
    */
    struct Node_user* iterator=head;
    if(strcmp(iterator->data.id,id)==0){
        head=iterator->next;
        free(iterator);
        return head;
    }
    while(iterator->next!=NULL){
        if(strcmp(iterator->next->data.id,id)==0){
            char path[100];
            sprintf(path, "%s/transactions.csv", iterator->next->data.username);
            remove(path);
            sprintf(path, "%s/customers.csv", iterator->next->data.username);
            remove(path);
            sprintf(path, "%s/accounts.csv", iterator->next->data.username);
            remove(path);
            sprintf(path, "%s/log.txt", iterator->next->data.username);
            remove(path);
            sprintf(path, "%s", iterator->next->data.username);
            char cmd[100];
            sprintf(cmd, "rmdir %s", path);
            int ret = system(cmd);
            struct Node_user* copy=iterator->next;
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

void modify_user_by_id(struct Node_user *head, char id_string[], char pass[]) {
    /**
    * param: struct Node_account*, char[], float
    * description: modifies an account with a given id and data in the dynamically allocated list
    * return: void
    */
    struct Node_user* iterator=head;
    while(iterator!=NULL){
        if(strcmp(iterator->data.id,id_string)==0){
            strcpy(iterator->data.password, pass);
            return;
        }
        iterator=iterator->next;
    }
}