#include <stdio.h>
#include <string.h>

void possibilities(char last,int step);
void show(int step);

char input[20];
char sorted[20];
int printFlag = 0;
int strL = 0;
int main(){
    
    scanf("%s",input);
    strL = strlen(input);
    int flag = 1;
    while(flag){
        flag = 0;
        for(int i = 1;i < strL;i++){
            if(input[i] < input[i-1]){
                char temp = input[i];
                input[i] = input[i-1];
                input[i-1] = temp;
                flag = 1;
            }
        }
    }
    possibilities(-1,0);
    printf("\n");
    //printf("%s",input);
    return 0;
}
void possibilities(char last,int step){
    if(step >= 4){
        show(step);
    }
    for(int i = last+1;i<strL;i++){
        sorted[step] = input[i];
        possibilities(i,step+1);
    }
}
void show(int step){
    if(printFlag)printf(", ");
    printFlag = 1;
    for(int i = 0;i<step;i++){
        printf("%c",sorted[i]);
    }
}
