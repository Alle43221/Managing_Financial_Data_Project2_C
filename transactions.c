#include "transactions.h"

void save_deposit(struct Node_account* head, char global_user[]){
    /**
     * param: struct Node_account*, char[]
     * description: saves the transactional information of a cash deposit if the account associated with
     *                  the given iban is administrated by the program
     * exception: Error opening file at path
     * return: void
     */
    char value_string[10], iban[25];
    float value;
    int iban1=0, value1=0;
    while(iban1==0){
        printf("Enter the account iban:\n");
        scanf("%25s", iban);
        iban1+=validare_iban(iban);
        if(iban1==0){
            printf("Invalid iban!\n");
        }
    }

    while(value1==0){
        printf("Enter the amount:\n");
        scanf("%10s", value_string);
        value1+= validate_amount(value_string);
        if(value1==0){
            printf("Invalid value!\n");
        }
    }
    value=atof(value_string);
    value=value*100;
    value=roundf(value);
    value/=100;

    char cod_banca[5], cod_tara[3];
    strncpy(cod_banca, iban+4, 4);
    strncpy(cod_tara, iban, 2);
    cod_tara[2]='\0';
    char buffer1[50];
    time_t t1 = time(0);
    struct tm *info = localtime( &t1 );
    if(strcmp(cod_banca, "ALMO")==0 && strcmp(cod_tara, "RO")==0){
        char cod_client[17], cod_cont[3];
        strncpy(cod_client, iban+8, 17);
        strncpy(cod_cont, iban+2, 2);

        char username[50], password[50], buffer[100], user_id[17];
        FILE *file=fopen("users.txt", "r");
        if(file==NULL){
            printf("Error opening file at %s\n", "users.txt");
            return;
        }
        int gasit=0;
        while(fgets(buffer, 100, file)) {
            strcpy(username, strtok(buffer, " \n"));
            strcpy(password, strtok(NULL, " \n"));
            strcpy(user_id, strtok(NULL, " \n"));
            if (strcmp(user_id, cod_client)==0){
                gasit=1;

                char path[100];
                sprintf(path, "./%s/log.txt",username);
                FILE *file1=fopen(path, "a");
                if(file==NULL){
                    printf("Error opening file at %s\n", path);
                    return;
                }
                time_t t;
                time(&t);
                char str[100];
                sprintf(str, "Deposited %0.2f in account with iban %s at %s",value, iban,ctime(&t));
                fwrite(str, 1, strlen(str), file1);
                fclose(file1);

                sprintf(path, "./%s/transactions.txt", global_user);
                FILE *file2 = fopen(path, "a");
                if(file2==NULL){
                    printf("Error opening file at %s\n", "users.txt");
                    return;
                }

                strftime(buffer1,50,"%d:%m:%Y,%H:%M:%S", info);
                sprintf(str, "deposit,+%0.2f,%s,%s\n", value, buffer1, iban);
                fwrite(str, 1, strlen(str), file2);
                fclose(file2);

                modify_account_by_id(head, cod_cont, value);
                save_accounts_to_file(head, username);
            }
        }
        if(gasit==0){
            printf("Invalid iban!\n");
        }
        fclose(file);
    }
    else{
        char path[100];
        sprintf(path, "./%s/log.txt", global_user);
        FILE *file1=fopen(path, "a");
        if(file1==NULL){
            printf("Error opening file at %s\n", path);
            return;
        }
        time_t t;
        time(&t);
        char str[100];
        sprintf(str, "Deposited %0.2f in account with iban %s at %s",value, iban,ctime(&t));
        fwrite(str, 1, strlen(str), file1);
        fclose(file1);

        sprintf(path, "./%s/transactions.txt", global_user);
        FILE *file2 = fopen(path, "a");
        if(file2==NULL){
            printf("Error opening file at %s\n", "users.txt");
            return;
        }

        strftime(buffer1,50,"%d:%m:%Y,%H:%M:%S", info);
        sprintf(str, "deposit,+%0.2f,%s,%s\n", value, buffer1, iban);
        fwrite(str, 1, strlen(str), file2);
        fclose(file2);
    }
    printf("Successful deposit!\n");
}

void save_withdrawal(struct Node_account *head, char user_id[], char  global_user[]) {
    /**
     * param: struct Node_account*, char[], char[]
     * description: saves the transactional information of a cash withdrawal if the account associated with
     *          the given iban is administrated by the program and the user has access to it
     * exception: Error opening file at path
     *            Permission denied
     * return: void
     */
    char value_string[10], iban[25];
    float value;
    int iban1=0, value1=0;
    while(iban1==0){
        printf("Enter the account iban:\n");
        scanf("%25s", iban);
        iban1+=validare_iban(iban);
        if(iban1==0){
            printf("Invalid iban!\n");
        }
    }

    while(value1==0){
        printf("Enter the amount:\n");
        scanf("%10s", value_string);
        value1+= validate_amount(value_string);
        if(value1==0){
            printf("Invalid value!\n");
        }
    }
    value=atof(value_string);
    value=value*100;
    value=roundf(value);
    value/=100;

    char cod_banca[5], cod_tara[3];
    strncpy(cod_banca, iban+4, 4);
    strncpy(cod_tara, iban, 2);
    cod_tara[2]='\0';
    if(strcmp(cod_banca, "ALMO")==0 && strcmp(cod_tara, "RO")==0){
        char cod_client[17], cod_cont[3];
        strncpy(cod_client, iban+8, 17);
        strncpy(cod_cont, iban+2, 2);
        if (strcmp(user_id, cod_client)==0) {
            char path[100];
            sprintf(path, "./%s/log.txt", global_user);
            FILE *file1 = fopen(path, "a");
            if(file1==NULL){
                printf("Error opening file at %s\n", "users.txt");
                return;
            }
            time_t t;
            time(&t);
            char str[100];
            sprintf(str, "Withdraw %0.2f from account with iban %s at %s", value, iban, ctime(&t));
            fwrite(str, 1, strlen(str), file1);
            fclose(file1);

            sprintf(path, "./%s/transactions.txt", global_user);
            FILE *file2 = fopen(path, "a");
            if(file2==NULL){
                printf("Error opening file at %s\n", "users.txt");
                return;
            }
            time_t t1;
            struct tm* info = localtime( &t1 );
            char buffer[50];
            strftime(buffer,50,"%d:%m:%Y,%H:%M:%S", info);
            sprintf(str, "withdrawal,-%0.2f,%s,%s\n", value,  buffer,iban);
            fwrite(str, 1, strlen(str), file2);
            fclose(file2);

            modify_account_by_id(head, cod_cont, value*(-1.0));
            save_accounts_to_file(head, global_user);
            printf("Successful withdrawal!\n");
        }
        else {
            printf("Permission denied/Invalid iban!\n");
        }
    }
}

void save_transfer(struct Node_account* head, char user_id[], char global_user[]) {
    /**
    * param: struct Node_account*, char[], char[]
    * description: saves the transactional information of a transfer if the source-account associated with
    *          the given iban is administrated by the program and the user has access to it
    * exception: Error opening file at path
    *            Permission denied
    * return: void
    */
    char value_string[10], iban[25], iban2[25];
    float value;
    int iban1 = 0, value1 = 0;
    while (iban1 == 0) {
        printf("Enter the source account iban:\n");
        scanf("%25s", iban);
        iban1 += validare_iban(iban);
        if (iban1 == 0) {
            printf("Invalid iban!\n");
        }
    }

    iban1 = 0;
    while (iban1 == 0) {
        printf("Enter the destination account iban:\n");
        scanf("%25s", iban2);
        iban1 += validare_iban(iban2);
        if (iban1 == 0) {
            printf("Invalid iban!\n");
        }
    }

    while (value1 == 0) {
        printf("Enter the amount:\n");
        scanf("%10s", value_string);
        value1 += validate_amount(value_string);
        if (value1 == 0) {
            printf("Invalid value!\n");
        }
    }
    value = atof(value_string);
    value = value * 100;
    value = roundf(value);
    value /= 100;

    char cod_banca[5], cod_tara[3];
    strncpy(cod_banca, iban + 4, 4);
    cod_banca[4] = '\0';
    strncpy(cod_tara, iban, 2);
    cod_tara[2] = '\0';

    char cod_banca2[5], cod_tara2[3];
    strncpy(cod_banca2, iban2 + 4, 4);
    cod_banca2[4] = '\0';
    strncpy(cod_tara2, iban2, 2);
    cod_tara2[2] = '\0';

    char cod_client[17], cod_cont[3];
    strncpy(cod_client, iban + 8, 17);
    strncpy(cod_cont, iban + 2, 2);

    char cod_client_destination[17], cod_cont_destination[3];
    strncpy(cod_client_destination, iban2 + 8, 17);
    strncpy(cod_cont_destination, iban2 + 2, 2);

    if (strcmp(cod_banca, "ALMO") == 0 && strcmp(cod_tara, "RO") == 0) {
        if (strcmp(cod_client, user_id) == 0) {
            time_t t1 = time(0);
            struct tm *info = localtime( &t1 );
            char buffer1[50];
            strftime(buffer1,50,"%d:%m:%Y,%H:%M:%S", info);

            if (strcmp(cod_banca2, "ALMO") == 0 && strcmp(cod_tara2, "RO") == 0) {

                char username[50], password[50], buffer[100], user_id_destination[17];
                FILE *file = fopen("users.txt", "r");
                int gasit = 0;
                while (fgets(buffer, 100, file)) {
                    strcpy(username, strtok(buffer, " \n"));
                    strcpy(password, strtok(NULL, " \n"));
                    strcpy(user_id_destination, strtok(NULL, " \n"));
                    if (strcmp(user_id_destination, cod_client_destination) == 0) {
                        gasit = 1;

                        char path[100];
                        sprintf(path, "./%s/log.txt", username);
                        FILE *file1 = fopen(path, "a");
                        if(file1==NULL){
                            printf("Error opening file at %s\n", "users.txt");
                            return;
                        }
                        time_t t;
                        time(&t);
                        char str[100];
                        sprintf(str, "Received %0.2f from account with iban %s in account with iban %s at %s", value, iban, iban2, ctime(&t));
                        fwrite(str, 1, strlen(str), file1);
                        fclose(file1);

                        sprintf(path, "./%s/transactions.txt", username);
                        FILE *file2 = fopen(path, "a");
                        if(file2==NULL){
                            printf("Error opening file at %s\n", "users.txt");
                            return;
                        }
                        strftime(buffer1,50,"%d:%m:%Y,%H:%M:%S", info);
                        sprintf(str, "transfer,+%0.2f,%s,%s,%s\n", value, buffer1,iban2, iban);
                        fwrite(str, 1, strlen(str), file2);
                        fclose(file2);

                        struct Node_account *head1=NULL;
                        head1=load_accounts(head1, username);
                        modify_account_by_id(head1, cod_cont_destination, value);
                        save_accounts_to_file(head1, username);
                    }
                }
                fclose(file);
                if (gasit == 0) {
                    printf("Invalid iban!\n");
                    return;
                }
            }
            modify_account_by_id(head, cod_cont, value*(-1.0f));
            save_accounts_to_file(head, global_user);

            char path[100];
            sprintf(path, "./%s/log.txt", global_user);
            FILE *file1 = fopen(path, "a");
            if(file1==NULL){
                printf("Error opening file at %s\n", "users.txt");
                return;
            }
            time_t t;
            time(&t);
            char str[100];
            sprintf(str, "Transferred %0.2f from account with iban %s in account with iban %s at %s", value, iban, iban2, ctime(&t));
            fwrite(str, 1, strlen(str), file1);
            fclose(file1);

            sprintf(path, "./%s/transactions.txt", global_user);
            FILE *file2 = fopen(path, "a");

            if(file2==NULL){
                printf("Error opening file at %s\n", "users.txt");
                return;
            }
            sprintf(str, "transfer,-%0.2f,%s,%s,%s\n", value, buffer1,iban, iban2);
            fwrite(str, 1, strlen(str), file2);
            fclose(file2);

            printf("Successful transaction!\n");
        }
        else{
            printf("Permission denied!\n");
        }
    } else {
        printf("Permission denied!\n");
    }
}
