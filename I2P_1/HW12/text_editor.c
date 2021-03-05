#include <stdio.h>
#include <ctype.h>
#include <string.h>

char input[1000];
char string[1000];
int cursor = 0;
int main(){
    fgets(input, 1000, stdin);
    for(int i = 0;i<strlen(input);i++){
        if(input[i] == '/'){
            switch(input[i+1]){
                case 'b':
                    if(cursor > 0){
                        string[cursor-1] = '#';
                        cursor--;
                    }
                    i += 9;
                    break;
                case 'n':
                    string[cursor] = '\n';
                    cursor++;
                    i += 7;
                    break;
                case 'l':
                    if(cursor > 0){
                        cursor--;
                    }
                    i += 4;
                    break;
                case 'r':
                    if(cursor < strlen(string)){
                        cursor++;
                    }
                    i += 5;
                    break;
            }
        }else{
            if(string[cursor] != 0){
                for(int j = strlen(string);j > cursor;j--){
                    if(string[j-1] != '#'){
                        printf("%c %c\n",string[j],string[j-1]);
                        string[j] = string[j-1];
                    }
                }
            }
            string[cursor] = input[i];
            cursor++;
        }
    }
    for(int i = 0;i<strlen(string);i++){
        if(string[i] != '#'){
            printf("%c",string[i]);
        }
    }
    
    return 0;
}