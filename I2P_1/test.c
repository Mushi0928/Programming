#include <stdio.h>
#include <stdlib.h>

int N;
int valid = 0;
int value[16];
int person[3] = {0};
void findNext(int num);
int main(){
    scanf("%d",&N);
    for(int i = 0;i<N;i++){
        scanf("%d",value + i);
    }
    findNext(0);
    printf("%s",valid?"YES":"NO");
}
void findNext(int num){
    if(valid == 1 || num == N){
        if(person[0] == person[1] && person[1] == person[2]){
            valid = 1;
        }
        return;
    }
    for(int i = 0;i<3;i++){
        person[i] += value[num];
        findNext(num + 1);
        person[i] -= value[num];
    }
}