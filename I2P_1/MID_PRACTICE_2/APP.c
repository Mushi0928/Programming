#include <stdio.h>

void pickNext(int cur,int step);
int isPalin(int step);

int n,k;
int valid = 0;
char str[1005];
int taken[1005] = { 0 };
int main(){
    scanf("%d %d",&n,&k);
    scanf("%s",str);
    pickNext(0,0);
    printf("%s",(valid)?"Yes\n":"No\n");
}
void pickNext(int cur,int step){
    if(step == k){
        isPalin(step);
        return;
    }else{
        if(isPalin(step))return;
        for(int i = cur;i<n-k+step&&!valid;i++){
            taken[i] = 1;   
            pickNext(i+1,step+1);
            taken[i] = 0;
        }
    }
}
int isPalin(int step){
    /**
    for(int i = 0;i<n;i++){
        if(!taken[i]){
            printf("%c",str[i]);
        }
    }
    printf("\n");
    **/
    int leftFlag = 0;
    int rightFlag = n-1;
    for(int i = 0;i<(n-step)/2;i++){
        while(taken[leftFlag])leftFlag++;
        while(taken[rightFlag])rightFlag--;
        //printf("%c %c\n",str[leftFlag],str[rightFlag]);
        if(str[leftFlag] != str[rightFlag]){
            return 0;
        }
        leftFlag++;
        rightFlag--;
    }
    valid = 1;
    return 1;
}