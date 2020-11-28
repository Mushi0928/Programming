#include <stdio.h>

int main(){
    int N,Q;

    scanf("%d %d",&N,&Q);
    int plates[N];
    int queries[Q][2];

    for(int i = 0;i<N;i++){
        scanf("%d",&plates[i]);
    }
    for(int i = 0;i<Q;i++){
        int start,end,count = 0;
        int bacteria[32] = { 0 };
        scanf("%d %d",&start,&end);

        for(int j = start;j<=end;j++){
            if(bacteria[plates[j]] == 0){
                count++;
            }
            bacteria[plates[j]]++;
        }
        printf("%d\n",count);
    }
    return 0;
}