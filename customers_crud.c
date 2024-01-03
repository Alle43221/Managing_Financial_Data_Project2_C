#include "customers_crud.h"

void save_customers_to_file(struct Node_customer *head, char global_user[]){
    /**
     * param: struct Node_customer*, char[]
     * return: void
     * description: saves all the customers in dynamically allocated list starting at address head to file .../customers.txt
     * exception: Error opening file at path
     */
    char path[100];
    sprintf(path, "./%s/customers.txt",global_user);
    FILE *file1=fopen(path, "w");
    if(file1==NULL){
        printf("Error opening file at %s\n", path);
        return;
    }
    struct Node_customer* iterator=head;
    while(iterator!=NULL){
        char str[100];
        sprintf(str, "%s,%s,%s,%s,%s\n",iterator->data.id_string,iterator->data.name, iterator->data.iban, iterator->data.phone, iterator->data.email);
        fwrite(str, 1, strlen(str), file1);
        iterator=iterator->next;
    }
    fclose(file1);
}

struct Node_customer * delete_customer(struct Node_customer *head, char global_user[]){
    /**
    * param: struct Node_customer*, char[]
    * return: struct Node_customer* (current starting address for list)
    * description: deletes a customer identified by id from the list starting at head and from the .../customers.txt file
    * exception: Error opening file at path
     *           Customer not found
    */
    int id1=0;
    char id_string[10]="";
    while (id1==0){
        printf("Enter customer id:\n");
        scanf("%10s", id_string);
        id1= validare_id(id_string);
        if(id1!=1){
            printf("Invalid id!\n");
        }
    }
    int rez= check_id_customer(head, id_string);
    head=delete_by_id_customer(head, id_string);
    if(rez==0){
        printf("Customer deleted with success!\n");
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

        save_customers_to_file(head, global_user);
        fclose(file1);
    }
    else
        printf("Customer not found!\n");
    return head;
}

void modify_customer(struct Node_customer *head, char global_user[]){
    /**
    * param: struct Node_customer*, char[]
    * return: void
    * description: modify a customer identified by id from the list starting at head and into the .../customers.txt file
    * exception: Error opening file at path
     *           Customer not found
    */
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
        id1= validare_id(id_string);
        if(id1!=1){
            printf("Invalid id!\n");
        }
    }
    if(check_id_customer(head, id_string)==1){
        printf("Customer not found!\n");
    }
    else{
        modify_by_id_customer(head, id_string, name, iban, phone, email);

        printf("Customer modified with success!\n");
        char path[100];
        sprintf(path, "./%s/log.txt",global_user);

        FILE *file1=fopen(path, "a");
        if(file1==NULL){
            printf("Error opening file at %s\n", path);
            return;
        }
        time_t t;
        time(&t);
        char str[100];
        sprintf(str, "Modified customer with id %s at %s",id_string,ctime(&t));
        fwrite(str, 1, strlen(str), file1);

        save_customers_to_file(head, global_user);
        fclose(file1);
    }


}

struct Node_customer* add_customer(struct Node_customer *head, char global_user[]){
    /**
    * param: struct Node_customer*, char[]
    * return: struct Node_customer* (current address of the start of the list)
    * description: adds a new customer to the list starting at head and into the .../customers.txt file
    * exception: Error opening file at path
    */
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
        id1= validare_id(id_string);
        id1+= check_id_customer(head, id_string);
        if(id1!=2){
            printf("Invalid/Existing id!\n");
            id1=0;
        }
    }

    head=insert_at_end_customer(head, name, iban, phone, id_string, email);

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
    sprintf(str, "Added customer with id %s at %s",id_string,ctime(&t));
    fwrite(str, 1, strlen(str), file1);
    fclose(file1);

    sprintf(path, "./%s/customers.txt",global_user);
    FILE *file=fopen(path, "a");
    if(file==NULL){
        printf("Error opening file at %s\n", path);
        return head;
    }
    sprintf(str, "%s,%s,%s,%s,%s\n",id_string,name, iban, phone, email);
    fwrite(str, 1, strlen(str), file);
    fclose(file);
    printf("Customer added with success!\n");
    return head;
}

struct Node_customer* load_customers(struct Node_customer *head, char global_user[]){
    /**
     * param: struct Node_customer*, char[]
     * return: struct Node_customer* (current address of the start of the list)
     * description: loads all the customers in dynamically allocated list starting at address head from file .../customers.txt
     * exception: Error opening file at path
     */
    char path[100], str[100];
    sprintf(path, "./%s/customers.txt",global_user);
    FILE *file=fopen(path, "r");
    if(file==NULL){
        printf("Error opening file at %s\n", path);
        return head;
    }
    while(fgets(str, 100, file)){
        char *id= strtok(str, ",\n");
        char *name=strtok(NULL, ",\n");
        char *iban=strtok(NULL, ",\n");
        char *phone=strtok(NULL, ",\n");
        char *email=strtok(NULL, ",\n");
        head=insert_at_end_customer(head, name, iban, phone, id, email);
    }
    fclose(file);
    return head;
}

void print_all_customers(struct Node_customer *head) {
    /**
     * param: struct Node_customer*
     * return: void
     * description: prints all the customers from the dynamically allocated list starting at address head
     * exception: No customers available
     */
    struct Node_customer* iterator=head;
    if(head==NULL)
        printf("No customers available!\n");
    else
    while(iterator!=NULL){
        printf("%s %s %s %s %s\n", iterator->data.id_string, iterator->data.name, iterator->data.iban, iterator->data.phone, iterator->data.email);
        iterator=iterator->next;
    }
}