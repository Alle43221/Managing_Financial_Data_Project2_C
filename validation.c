#include "validation.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

int validare_id_customer(char x[]) {
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
