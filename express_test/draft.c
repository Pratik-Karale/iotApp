#include<stdio.h>
char parseStr(char *string[]){
        char *delim = " ";
        unsigned count = 0;
        /* First call to strtok should be done with string and delimiter as first and second parameter*/
        char *token = strtok(string,delim);
        count++;

        /* Consecutive calls to the strtok should be with first parameter as NULL and second parameter as delimiter
         * * return value of the strtok will be the split string based on delimiter*/
while(token != NULL)
        {
printf("Token no. %d : %s \n", count,token);
                token = strtok(NULL,delim);
                count++;
        }
        return 0;
}
void main(){
    parseStr("hello bitch");
}