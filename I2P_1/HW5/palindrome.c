#include <stdio.h>
#include <string.h>

int main(){
    char word[100000];
    unsigned long str;
    int isPalin;
    while (scanf("%s",word) != EOF){
        isPalin = 1;
        str = strlen(word);
        //printf("a");
        for(int i = 0;i < str/2;i++){
            if(word[i] != word[str - i - 1]){
                isPalin = 0;
                str = 0;
                //break;
            }
        }
        if(isPalin == 1){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}