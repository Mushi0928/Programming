#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void jump(int now,int end,int step);
int cost(int step);

int h[30];
int route[30];
int least_cost = __INT_MAX__;
int least_step = __INT_MAX__;

int main(){
    int N;
    scanf("%d",&N);
    for(int i = 0;i<N;i++){
        scanf("%d",&h[i]);
    }
    jump(0,N-1,1);
    printf("%d %d\n",least_cost,least_step);

}
void jump(int now,int end,int step){
    if(now > end){
        return;
    }
    if(now == end){
        int temp = cost(step);
        if(temp<least_cost){
            least_cost = temp;
            least_step = step-1;
        }else if(temp == least_cost){
            if(step-1 < least_step)least_step = step-1;
        }
        return;
    }

    for(int i = 1;i<=2;i++){
        route[step] = now + i;
        jump(now+i,end,step+1);
    }
}
int cost(int step){
    int ans = 0;
    /*
    for(int i = 0;i<step;i++){
        printf("%d ",route[i]);
    }
    */
    
    for(int i = 1;i<step;i++){
        ans += abs(h[route[i]] - h[route[i-1]]);
    }
    //printf("SUM:%d\n",ans);
    return ans;
}