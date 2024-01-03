#include "validation.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stdlib.h"

int validare_string(char x[]){
    /**
    * param: char[]
    * description: validates an array of characters
    * return: int
    * exceptions: array contains spaces -> return 0
    *             array contains commas -> return 0
    *             array contains digits -> return 0
    */
    if (strlen(x)==0)
        return 0;
    int len=strlen(x);
    char digits[]="0123456789";
    for(int i=0; i<len; i++){
        if(x[i]==' ')
            return 0;
        else if(strchr(digits, x[i]))
            return 0;
        else if(x[i]==',')
            return 0;
    }
    return 1;
}

int validare_iban(char x[]){
    /**
    * param: char[]
    * description: validates an iban code
    * return: int
    * exceptions: code doesn't comply with the format "AB49ABCD1B31007593840000"
     *  first two characters -> letters
     *  next two characters -> digits
     *  next four characters -> letters
     *  remaining characters -> alphanumeric characters
     *  total of 24 characters
    */
    if (strlen(x)!=24)
        return 0;
    if(!isalpha(x[0])|| !isalpha(x[1]))
        return 0;
    if(!isdigit(x[2])|| !isdigit(x[3]))
        return 0;
    if(!isalpha(x[4])|| !isalpha(x[5])|| !isalpha(x[6])|| !isalpha((x[7])))
        return 0;

    int len=strlen(x);
    for(int i=8; i<len; i++){
        if(!isdigit(x[i])&&!isalpha(x[i]))
            return 0;
    }
    return 1;
}

int validare_phone(char x[]) {
    /**
      * param: char[]
      * description: validates a phone number
      * return: int
      * exceptions: number contains non-numeric characters
      *  total of 10 characters
      */
    int len=strlen(x);
    if(len!=10)
        return 0;
    for(int i=0; i<len; i++){
        if(!isdigit(x[i]))
            return 0;
    }
    return 1;
}

int validare_id(char x[]) {
    /**
    * param: char[]
    * description: validates an id
    * return: int
    * exceptions: number contains non-numeric characters
    */
    int len=strlen(x);
    if(len==0)
        return 0;
    for(int i=0; i<len; i++){
        if(!isdigit(x[i]))
            return 0;
    }
    return 1;
}

int validare_email(char x[]) {
    /**
    * param: char[]
    * description: validates an email address
    * return: int
    * exceptions: array doesn't contain the symbol "@"
    */
    int len=strlen(x);
    if(len==0)
        return 0;
    const char simbol='@';
    if(strchr(x, simbol)==NULL)
        return 0;
    return 1;
}

int validate_amount(char s[]){
    /**
    * param: char[]
    * return: integer (0/1)
    * description: checks if the string provided corresponds to a valid amount with at most two decimal places
    */
    int len=strlen(s);
    for(int i=0; i< len; i++){
        if(isdigit(s[i])==0 && s[i]!='.')
            return 0;
    }
    double amount=atof(s);
    if(amount<=0)
        return 0;
    if(amount>10000000)
        return 0;
    amount*=100.0;
    float epsilon=0.0000000001;
    if(abs(amount- (int) amount)>epsilon)
        return 0;
    return 1;
}

int check_username(char user[]){
    /**
    * param: char[]
    * return: integer (0/1)
    * description: checks if the string provided corresponds to an unique username
    */
    FILE *file=fopen("users.txt", "r");
    if(file==NULL){
        printf("Error opening file at %s\n", "users.txt");
        return 0;
    }
    char username[50], password[50], buffer[100], user_id[17];
    while(fgets(buffer, 100, file)) {
        strcpy(username, strtok(buffer, " \n"));
        strcpy(password, strtok(NULL, " \n"));
        strcpy(user_id, strtok(NULL, " \n"));
        if(strcmp(user, username)==0){
            return 0;
        }
    }
    return 1;
}

int check_user_id(char id[]) {
    /**
    * param: char[]
    * return: integer (0/1)
    * description: checks if the string provided corresponds to an unique id
    */
    FILE *file=fopen("users.txt", "r");
    if(file==NULL){
        printf("Error opening file at %s\n", "users.txt");
        return 0;
    }
    char username[50], password[50], buffer[100], user_id[17];
    while(fgets(buffer, 100, file)) {
        strcpy(username, strtok(buffer, " \n"));
        strcpy(password, strtok(NULL, " \n"));
        strcpy(user_id, strtok(NULL, " \n"));
        if(strcmp(id, user_id)==0){
            return 0;
        }
    }
    return 1;
}

int validate_password(char pass[]){
    /**
   * param: char[]
   * return: integer (0/1)
   * description: checks if the string provided corresponds to a valid password (has at least 4 characters and no spaces)
   */
    if(strlen(pass)<4)
        return 0;
    int l= strlen(pass);
    for (int i=0; i<l; i++){
        if(pass[i]==' '){
            return 0;
        }
    }
    return 1;
}
