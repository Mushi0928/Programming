#include <stdio.h>
#include <string.h>

void chooseNext(int step);
void show();

char password[25];
char encoded[25];
int chosen[25] = { 0 };
int passwordLength,encodedLength;

int main(){
    scanf("%s",password);
    scanf("%s",encoded);
    passwordLength = strlen(password);
    encodedLength = strlen(encoded);
    chosen[0] = 0;

    chooseNext(1);

    return 0;
}
void chooseNext(int step){
    char temp = encoded[step];
    if(step == encodedLength+1 || chosen[step-1] == passwordLength){
        show();
        return;
    }
    if(temp == '#'){
        for(int i = 1;i<passwordLength;i++){
            chosen[step] = chosen[step-1] + i;
            chooseNext(step+1);
            chosen[step] = chosen[step-1];
        }
    }else if(temp == password[chosen[step-1]+1]){
        chosen[step] = chosen[step-1] + 1;
        chooseNext(step+1);
        chosen[step] = chosen[step-1];
    }else{
        return;
    }
}
void show(){
    for(int i = 1;i<encodedLength;i++){
        for(int j = chosen[i-1];j<=chosen[i];i++){
            printf("%c",password[j]);
        }
        printf(" ");
    }
    printf("\n");
}
