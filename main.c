#include <stdio.h>
#include <string.h>
#include "time.h"
#include <ctype.h>
#include "stdlib.h"
#include "validation.h"
#include "dynamic_customers.h"

char global_user[50]="";

struct Node_customer* customers_head=NULL;

void insert_at_end_customer(struct Node_customer* head, char name[], char iban[], char phone[], char id[], char email[]){
    struct Node_customer* iterator=head;
    if(iterator==NULL){  //cazul in care este primul nod
        struct Node_customer* new_node= (struct Node_customer*) malloc(sizeof(struct Node_customer));
        new_node->next=NULL;
        strcpy(new_node->data.id_string, id);
        strcpy(new_node->data.phone, phone);
        strcpy(new_node->data.iban, iban);
        strcpy(new_node->data.name, name);
        strcpy(new_node->data.email, email);
        customers_head=new_node;
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
    }

}

int delete_by_id_customer(struct Node_customer* head, char id[]){
    struct Node_customer* iterator=head;
    if(strcmp(iterator->data.id_string, id)==0){
        customers_head=iterator->next;
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

void login_menu()
{
    /**
     * param: none
     * description: login function for the app
     * exception: invalid password -> new login
     *            invalid username -> new login
     * return: none
     */
    FILE *file=fopen("users.txt", "r");
    char username[50], password[50], buffer[100];
    char username1[50], password1[50];
    printf("Enter username:\n");
    scanf("%50s", username);
    printf("Enter password:\n");
    scanf("%50s", password);
    while(fgets(buffer, 100, file)){
        strcpy(username1, strtok(buffer, " \n"));
        strcpy(password1, strtok(NULL, " \n"));
        if(strcmp(username, username1)==0){
            if(strcmp(password, password1)==0){
                printf("Login successfully!\n");
                strcpy(global_user, username);

                char path[100];
                sprintf(path, "./%s/log.txt",username);

                FILE *file1=fopen(path, "a");
                time_t t;
                time(&t);
                char str[100];
                sprintf(str, "Login at %s",ctime(&t));
                fwrite(str, 1, strlen(str), file1);
                fclose(file1);

                fclose(file);
                return;
            }
            else{
                printf("Invalid password!\n");
                fclose(file);
                return;
            }

        }
    }
    fclose(file);
    printf("Invalid username!\n");
}

void welcome_text(){
    /**
    * param: none
    * description: prints a welcome message for the user
    * return: none
    */
    printf("---------------------------------------------\n");
    printf("| Welcome to the transaction manager!       |\n");
    printf("| Please follow the bellow steps to log in. |\n");
    printf("| Or type \"exit\" to stop the program.       |\n");
    printf("---------------------------------------------\n");
}

void menu_text(){
    /**
    * param: none
    * description: prints a list of menu options for the user
    * return: none
    */
    printf("---------------------------------------------\n");
    printf("| Menu:                                     |\n");
    printf("| 1. Add customer                           |\n");
    printf("| 2. Delete customer                        |\n");
    printf("| 3. Modify customer                        |\n");
    printf("---------------------------------------------\n");
}

void print_all(struct Node_customer *head) {
    struct Node_customer* iterator=head;
    while(iterator!=NULL){
        printf("%s\n", iterator->data.name);
        iterator=iterator->next;
    }
}

void save_customers_to_file(struct Node_customer *head){
    char path[100];
    sprintf(path, "./%s/customers.txt",global_user);
    FILE *file1=fopen(path, "w");
    struct Node_customer* iterator=head;
    while(iterator!=NULL){
        char str[100];
        sprintf(str, "%s,%s,%s,%s,%s\n",iterator->data.id_string,iterator->data.name, iterator->data.iban, iterator->data.phone, iterator->data.email);
        fwrite(str, 1, strlen(str), file1);
        iterator=iterator->next;
    }
    fclose(file1);
}

void delete_customer(){
    int id1=0;
    char id_string[10]="";
    while (id1==0){
        printf("Enter customer id:\n");
        scanf("%10s", id_string);
        id1= validare_id_customer(id_string);
        if(id1!=1){
            printf("Invalid id!\n");
        }
    }

    int rez=delete_by_id_customer(customers_head, id_string);
    if(rez){
        printf("Customer deleted with success!\n");
        char path[100];
        sprintf(path, "./%s/log.txt",global_user);

        FILE *file1=fopen(path, "a");
        time_t t;
        time(&t);
        char str[100];
        sprintf(str, "Deleted customer with id %s at %s",id_string,ctime(&t));
        fwrite(str, 1, strlen(str), file1);

        save_customers_to_file(customers_head);
        fclose(file1);
    }
    else
        printf("Customer not found!\n");
}

void modify_customer(){
    char name[50]="", iban[25]="", phone[11]="", id_string[10]="", email[50]="";
    int name1=0, iban1=0, phone1=0, id1=0, email1=0;

    while (name1==0){
        printf("Enter customer name:\n");
        scanf("%50s", name);
        name1=validare_string(name);
        if(name1==0){
            printf("Invalid name!\n");
        }
    }

    while (iban1==0){
        printf("Enter customer iban:\n");
        scanf("%25s", iban);
        iban1= validare_iban(iban);
        if(iban1==0){
            printf("Invalid iban!\n");
        }
    }

    while (phone1==0){
        printf("Enter customer phone number:\n");
        scanf("%11s", phone);
        phone1= validare_phone(phone);
        if(phone1==0){
            printf("Invalid phone number!\n");
        }
    }

    while (email1==0){
        printf("Enter customer email address:\n");
        scanf("%50s", email);
        email1= validare_email(email);
        if(email1==0){
            printf("Invalid email address!\n");
        }
    }

    while (id1==0){
        printf("Enter customer id:\n");
        scanf("%10s", id_string);
        id1= validare_id_customer(id_string);
        if(id1!=1){
            printf("Invalid id!\n");
        }
    }
    print_all(customers_head);
    if(check_id_customer(customers_head, id_string)==1){
        printf("Customer not found!\n");
    }
    else{
        modify_by_id_customer(customers_head, id_string, name, iban, phone, email);

        printf("Customer modified with success!\n");
        char path[100];
        sprintf(path, "./%s/log.txt",global_user);

        FILE *file1=fopen(path, "a");
        time_t t;
        time(&t);
        char str[100];
        sprintf(str, "Modified customer with id %s at %s",id_string,ctime(&t));
        fwrite(str, 1, strlen(str), file1);

        save_customers_to_file(customers_head);
        fclose(file1);
    }


}

void add_customer(){
    char name[50]="", iban[25]="", phone[11]="", id_string[10]="", email[50]="";
    int name1=0, iban1=0, phone1=0, id1=0, email1=0;

    while (name1==0){
        printf("Enter customer name:\n");
        scanf("%50s", name);
        name1=validare_string(name);
        if(name1==0){
            printf("Invalid name!\n");
        }
    }

    while (iban1==0){
        printf("Enter customer iban:\n");
        scanf("%25s", iban);
        iban1= validare_iban(iban);
        if(iban1==0){
            printf("Invalid iban!\n");
        }
    }

    while (phone1==0){
        printf("Enter customer phone number:\n");
        scanf("%11s", phone);
        phone1= validare_phone(phone);
        if(phone1==0){
            printf("Invalid phone number!\n");
        }
    }

    while (email1==0){
        printf("Enter customer email address:\n");
        scanf("%50s", email);
        email1= validare_email(email);
        if(email1==0){
            printf("Invalid email address!\n");
        }
    }

    while (id1==0){
        printf("Enter customer id:\n");
        scanf("%10s", id_string);
        id1= validare_id_customer(id_string);
        id1+= check_id_customer(customers_head, id_string);
        if(id1!=2){
            printf("Invalid/Existing id!\n");
        }
    }

    insert_at_end_customer(customers_head, name, iban, phone, id_string, email);

    char path[100];
    sprintf(path, "./%s/log.txt",global_user);

    FILE *file1=fopen(path, "a");
    time_t t;
    time(&t);
    char str[100];
    sprintf(str, "Added customer with id %s at %s",id_string,ctime(&t));
    fwrite(str, 1, strlen(str), file1);
    fclose(file1);

    sprintf(path, "./%s/customers.txt",global_user);
    FILE *file=fopen(path, "a");
    sprintf(str, "%s,%s,%s,%s,%s\n",id_string,name, iban, phone, email);
    fwrite(str, 1, strlen(str), file);
    fclose(file);
    printf("Customer added with success!\n");
}

void load_customers(){
    char path[100], str[100];
    sprintf(path, "./%s/customers.txt",global_user);
    FILE *file=fopen(path, "r");
    while(fgets(str, 100, file)){
        char *id= strtok(str, ",\n");
        char *name=strtok(NULL, ",\n");
        char *iban=strtok(NULL, ",\n");
        char *phone=strtok(NULL, ",\n");
        char *email=strtok(NULL, ",\n");
        insert_at_end_customer(customers_head, name, iban, phone, id, email);
    }

    fclose(file);
}

int main(){
    /**
     * param: none
     * description: console interface for transaction app
     * exception: ends the program on input "exit"
     */

    char menu_choice[100];
    welcome_text();
    while(strlen(global_user)==0){
        login_menu();
    }
    load_customers(customers_head);
    menu_text();
    while(strcmp(menu_choice, "exit")!=0){
        scanf("%100s", menu_choice);
        if(strcmp(menu_choice,"1")==0){
            add_customer();
        }
        else if(strcmp(menu_choice,"2")==0){
            delete_customer();
        }
        else if(strcmp(menu_choice,"3")==0){
            modify_customer();
        }
        else if(strcmp(menu_choice,"exit")==0){
            return 0;
        }
        else{
            printf("Invalid option!\n");
        }
    }
    return 0;
}