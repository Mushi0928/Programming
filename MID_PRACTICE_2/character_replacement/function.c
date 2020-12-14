#include "function.h"

int changeCharacter(char *str, char a, char b){
    int i = 0;
    char temp = str[0];
    while(temp != '\0'){
        if(temp == a){
            str[i] = b;
        }
        i++;
        temp = str[i];
    }
    return 0;
}