#include <stdio.h>
#include <stdlib.h>

int N,S,T;
int h[20];
int c[20];
int route[20] = { 0 };
int max_energy = 0;
int max_step = 0;

void jump(int current,int end,int step);
int cost(int step);

int main(){
    scanf("%d %d %d",&N,&S,&T);
    for(int i = 1;i<=N;i++){
        scanf("%d",&h[i]);
    }
    for(int i = 1;i<=N;i++){
        scanf("%d",&c[i]);
    }
    route[0] = S;
    jump(S,T,0);
    printf("%d %d\n",max_energy,max_step);
    return 0;
}
void jump(int current,int end,int step){
    if(current == end){
        int temp = cost(step);
        if(temp > max_energy){
            max_energy = temp;
            max_step = step;
        }else if(temp == max_energy && step > max_step){
            max_step = step;
        }
        route[current] = 0;
    }else{
        for(int i = 1;i<=N;i++){
            int flag = 1;
            for(int j = 0;j<=step;j++){
                if(route[j] == i)flag = 0;
            }
            //printf("cur: %d,i: %d,c[cur]: %d,c[i]: %d,step: %d,flag: %d\n",
            //        current,i,c[current],c[i],step,flag);
            if((c[i] == c[current] || i == current + 1 || i == current - 1) && flag){
                route[step+1] =  i;
                jump(i,end,step+1);
                route[step+1] = 0;
            }
        }
    }
}
int cost(int step){
    int sum = 0;
    /*
    for(int i = 0;i<=step;i++){
        printf("%d ",route[i]);
    }
    */
    for(int i = 1;i<=step;i++){
        sum += abs((route[i] - route[i-1]) * (h[route[i]] - h[route[i-1]]));
    }
    //printf("    cost: %d\n",sum);
    return sum;
}