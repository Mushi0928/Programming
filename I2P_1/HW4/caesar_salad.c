#include <stdio.h>
//ASCII of 'A' = 65
int main(){
    char word[3];
    int shift = 0;

    scanf("%c %c %c",&word[0],&word[1],&word[2]);
    scanf("%d",&shift);

    int i = 0;
    while(i < 3){
        /*
        int N = word[i] + shift%26;
        if(N > 'Z'){
            printf("%c",N - 26);
        }else if(N < 'A'){
            printf("%c",N + 26);
        }else{
            printf("%c",N);
        }
        */
        int N = word[i] + shift;
        if(N > 'Z'){
            printf("%c",(N-'A')%26+'A');
        }else if(N < 'A'){
            printf("%c",(N-'A')%26+91);
        }else{
            printf("%c",N);
        }
        i++;
    }
    printf("\n");
    return 0;
}