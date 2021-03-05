
//failed

#include <stdio.h>

void diet(int current,int lastPicked);

int N,K;
int valid = 0;
int c[25];

int main(){
    
    scanf("%d %d",&N,&K);

    for(int i = 0;i<N;i++){
        scanf("%d",&c[i]);
    }
    diet(0,0);
    printf("%s",valid?"YES\n":"NO\n");

}
void diet(int current,int lastPicked){
    if(current == K){
        valid = 1;
    }else{
        for(int i = lastPicked+1;i<N;i++){
            if(valid)return;
            if((current + c[i]) <= K){
                diet(current + c[i],i);
            }
        }
    }
}
