#include "reports.h"

int check_date_in_interval(struct tm start_date, struct tm end_date, struct tm item){
    /**
     * param: tm datetime object, tm datetime object, tm datetime object
     * return: integer (0/1)
     * description: checks if argument item is between two given dates
     * preconditions: validity of transaction information
     */
    struct tm new_date;
    new_date.tm_year=item.tm_year;
    new_date.tm_mon=item.tm_mon;
    new_date.tm_mday=item.tm_mday;
    new_date.tm_hour=0;
    new_date.tm_min=0;
    new_date.tm_sec=0;
    new_date.tm_isdst=0;
    new_date.tm_yday=0;
    new_date.tm_wday=0;
    int s_date=mktime(&start_date);
    int e_date=mktime(&end_date);
    int item_date=mktime(&new_date);
    long long int dif1=item_date-s_date;
    long long int dif2=e_date-item_date;
    if(dif1>=0 && dif2>=0)
        return 1;
    return 0;
}

struct tm transform_char_to_tm(char s[]){
    /**
     * param: char[]
     * return: tm datetime object
     * description: converts the date from format "DD:MM:YYYY" to a tm object
     * preconditions: validity of date
     */
    struct tm date;
    char copy[250];
    strcpy(copy, s);
    char *p=strtok(s, ":");
    date.tm_mday=atoi(p);
    p= strtok(NULL, ":");
    date.tm_mon=atoi(p)-1;
    p= strtok(NULL, ":");
    date.tm_year=atoi(p)-1900;
    date.tm_sec=0;
    date.tm_hour=0;
    date.tm_min=0;
    date.tm_isdst=0;
    return date;
}

int validate_date_format(char s[]){
    /**
     * param: char[]
     * return: integer (0/1)
     * description: checks if the string provided respects the imposed "DD:MM:YYYY" format
     */
    char copy[250];
    strcpy(copy, s);
    if(strlen(s)!=10){
        return 0;
    }
    char *p;
    p=strtok(s, ":");
    if(strlen(p)!=2){
        return 0;
    }
    if(!isdigit(*p) || !isdigit(*(p+1))) {
        return 0;
    }
    p= strtok(NULL, ":");
    if(strlen(p)!=2){
        return 0;
    }
    if(!isdigit(*p) || !isdigit(*(p+1))) {
        return 0;
    }
    p= strtok(NULL, ":");
    if(strlen(p)!=4){
        return 0;
    }
    if(!isdigit(*p) || !isdigit(*(p+1)) || !isdigit(*(p+2))|| !isdigit(*(p+3))) {
        return 0;
    }
    strcpy(s, copy);
    return 1;
}

void generate_account_statement(char global_user[], struct Node_account* head) {
    /**
     * param: char[], struct Node_account*
     * description: generates an account statement containing basic information about account (user, iban),
     *                  interval of time for transactions (last month) and expense & income report
     *              saves the report in a new file named statement-<date and time>.txt
     * return: none
     */
    char iban[25];
    int iban1=0;
    while(iban1==0){
        printf("Enter the account iban:\n");
        scanf("%25s", iban);
        iban1+=validare_iban(iban);
        if(iban1==0){
            printf("Invalid iban!\n");
        }
    }
    char cod_banca[5], cod_tara[3];
    strncpy(cod_banca, iban+4, 4);
    cod_banca[4]='\0';
    strncpy(cod_tara, iban, 2);
    cod_tara[2]='\0';

    char buffer1[50], buffer2[50];
    time_t t1 = time(0);
    struct tm *info = localtime( &t1 );
    strftime(buffer1,50,"%d_%m_%Y_%H_%M_%S", info);

    if(strcmp(cod_banca, "ALMO")==0 && strcmp(cod_tara, "RO")==0){
        char cod_client[17], cod_cont[3];
        strncpy(cod_client, iban+8, 17);
        cod_cont[2]='\0';
        strncpy(cod_cont, iban+2, 2);
        cod_client[16]='\0';
        if(check_id_account(head, cod_cont)!=1){
            char path[100];
            sprintf(path, "./%s/transactions.txt", global_user);
            FILE *file1 = fopen(path, "r");
            if(file1==NULL){
                printf("Error opening file at %s\n", "users.txt");
                return;
            }

            sprintf(path, "statement-%s.txt", buffer1);
            FILE *file2 = fopen(path, "w");
            fclose(file2);
            file2 = fopen(path, "w");
            if(file2==NULL){
                printf("Error opening file at %s\n", "users.txt");
                return;
            }

            char buffer[100], type[15], sum[15], date[15], time[10], iban2[25], copy[100];
            struct tm end_date=*info;
            end_date.tm_mon-=1;
            if(end_date.tm_mon<0){
                end_date.tm_year--;
                end_date.tm_mon=11;
            }
            strftime(buffer1,50,"%d:%m:%Y", info);
            strftime(buffer2,50,"%d:%m:%Y", &end_date);
            sprintf(copy, "Account statement generated for interval: %s to %s\n"
                          "For user: %s with account: %s\n", buffer1, buffer2, global_user, iban);
            fwrite(copy, 1, strlen(copy), file2);
            float expenses=0, income=0;
            while(fgets(buffer, 100, file1)){
                strcpy(copy, buffer);
                strcpy(type, strtok(buffer, ","));
                strcpy(sum, strtok(NULL, ","));
                strcpy(date, strtok(NULL, ","));
                strcpy(time, strtok(NULL, ","));
                strcpy(iban2, strtok(NULL, ",\n"));
                struct tm t_time= transform_char_to_tm(date);
                if(strcmp(iban2, iban)==0){
                    if(check_date_in_interval(end_date, *info, t_time)) {
                        fwrite(copy, 1, strlen(copy), file2);
                        if(sum[0]=='+'){
                            income+=atof(sum+1);
                        }
                        else{
                            expenses+=atof(sum+1);
                        }
                    }
                }
            }
            sprintf(copy, "Expenses: %0.2f, Income: %0.2f\n", expenses, income);
            fwrite(copy, 1, strlen(copy), file2);
            fclose(file1);
            fclose(file2);
            printf("Account statement generated!\n");

            sprintf(path, "./%s/log.txt", global_user);
            file1 = fopen(path, "a");
            if(file1==NULL){
                printf("Error opening file at %s\n", "users.txt");
                return;
            }
            sprintf(copy, "Generated account statement for account with iban: %s at %s", iban, ctime(&t1));
            fwrite(copy, 1, strlen(copy), file1);
            fclose(file1);
        }
        else{
            printf("Invalid iban!\n");
        }
    }
    else{
        printf("Permission denied!\n");
    }
}

int validate_date(char s[]){
    /**
    * param: char[]
    * return: integer (0/1)
    * description: checks if the string provided corresponds to a valid date
    * preconditions: the string respects the format "DD/MM/YYYY"
    */
    char copy[11];
    strcpy(copy, s);
    char *p=strtok(s, ":");
    int day= atoi(p);
    p=strtok(NULL, ":");
    int month= atoi(p);
    p=strtok(NULL, ":");
    int year= atoi(p);

    if(day<=0 || month<=0 || year<=0)
        return 0;
    if(year<1900)
        return 0;
    if(month>12)
        return 0;
    if(month==4 || month==6 || month==9 || month==11){
        if(day>30)
            return 0;
    }
    else if(month==2){
        if(year%16!=0 && year%4==0){
            if(day>29)
                return 0;
        }
        else
        if(day>28)
            return 0;
    }
    else{
        if(day>31)
            return 0;
    }
    strcpy(s, copy);
    return 1;
}

int validate_second_date(struct tm end_date, struct tm start_date){
    /**
   * param: tm datetime obj, tm datetime obj
   * return: integer (0/1)
   * description: checks if the first date comes before the second one
   * preconditions: the string respects the format "DD/MM/YYYY" and is a valid date
   */
    start_date.tm_year-=1900;
    end_date.tm_year-=1900;
    start_date.tm_hour=0;end_date.tm_hour=0;
    start_date.tm_sec=0;end_date.tm_sec=0;
    start_date.tm_min=0;end_date.tm_min=0;
    start_date.tm_isdst=0;end_date.tm_isdst=0;
    start_date.tm_mon-=1;end_date.tm_mon-=1;
    int end_date_int=mktime(&end_date);
    int start_date_int=mktime(&start_date);
    int diff_t=end_date_int-start_date_int;
    if(diff_t<0)
        return 0;
    return 1;
}