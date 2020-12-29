#include <stdio.h>
#include <ctype.h>
#include <string.h>

char target[25];
char string[1000];
char temp;
int flag = 0;
int count = 0;
int main(){
    scanf("%s",target);
    for(int i = 0;i<strlen(target);i++){
        target[i] = tolower(target[i]);
    }
    while(scanf("%c",&temp) != EOF){
        if(isalpha(temp)){
            if(flag){
                string[flag] = tolower(temp);
                flag++;
            }else{
                string[0] = tolower(temp);
                flag++;
            }
        }else if(flag){
            string[flag] = '\0';
            //printf("%s : %s\n",target,string);
            if(strcmp(string,target) == 0)
                count++;
            flag = 0;
        }
    }
    printf("%d\n",count);
    return 0;
}