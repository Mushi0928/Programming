#include <stdio.h>

int main(){
    int N,T;

    scanf("%d %d",&N,&T);
    double property[N],transfer[N],trans_rate[N][N];

    for(int i = 0;i<N;i++){
        scanf("%lf",&property[i]);
    }
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            scanf("%lf",&trans_rate[i][j]);
        }
    }
    for(int i = 0;i<T;i++){
        for(int j = 0;j<N;j++){
            for(int k = 0;k<N;k++){ //transfer jBank to kBank
                if(property[j] >= 10 && property[k] >= 10){
                    transfer[j] -= property[j]*trans_rate[j][k];
                    transfer[k] += property[j]*trans_rate[j][k];
                    //printf("bank %d gave bank %d %f dollars\n",j,k,property[j]*trans_rate[j][k]);
                }
            }
        }
        for(int j = 0;j<N;j++){
            property[j] += transfer[j];
            transfer[j] = 0;
        }
    }
    for(int i = 0;i<N;i++){
        printf("%.1lf\n",property[i]);
    }
    return 0;
}