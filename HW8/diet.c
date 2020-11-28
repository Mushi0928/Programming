#include <stdio.h>

void diet(int current,int lastPicked);
void resetTaken();

int N,K;
int valid = 0;
int c[25];
int taken[25];

int main(){
    
    scanf("%d %d",&N,&K);

    for(int i = 0;i<N;i++){
        scanf("%d",&c[i]);
    }
    resetTaken();
    diet(0,0);
    printf("%s",valid?"YES\n":"NO\n");

}
void diet(int current,int lastPicked){
    if(current == K){
        valid = 1;
    }else{
        for(int i = lastPicked;i<N;i++){
            if(valid)return;
            if(!taken[i] && (current + c[i]) <= K){
                taken[i] = 1;
                diet(current + c[i],i);
            }
        }
        taken[lastPicked] = 0;
    }
}
void resetTaken(){
    for(int i = 0;i<N;i++){
        taken[i] = 0;
    }
}