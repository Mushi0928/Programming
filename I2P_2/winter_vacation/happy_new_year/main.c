#include <stdio.h>

int N;
int max = 0;
int min = __INT_MAX__;

int main(){
    scanf("%d",&N);
    for(int i = 0;i<N+1;i++){
        int temp;
        scanf("%d",&temp);
        if(temp >= max)max = temp;
        if(temp <= min)min = temp;
    }
    printf("%d\n",(max-min)*2);
    return 0;
}