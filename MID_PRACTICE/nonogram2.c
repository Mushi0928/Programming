#include <stdio.h>

int main(){
    int T;
    scanf("%d",&T);

    for(int i = 0;i<T;i++){
        //declare variables
        int N,M;
        int valid = 1;
        scanf("%d %d",&N,&M);

        int rowQues[N][25],colQues[M][25];
        int rowQuesCount[N],colQuesCount[M];
        char nono[N][M];

        //scanning in questions
        for(int j = 0;j<N;j++){
            int numCount;
            scanf("%d",&numCount);
            rowQuesCount[j] = numCount;
            for(int k = 0;k<numCount;k++){
                scanf("%d",&rowQues[j][k]);
                //printf("%d ",rowQues[j][k]);
            }
            //printf("\n");
        }
        for(int j = 0;j<M;j++){
            int numCount;
            scanf("%d",&numCount);
            colQuesCount[j] = numCount;
            for(int k = 0;k<numCount;k++){
                scanf("%d",&colQues[j][k]);
                //printf("%d ",colQues[j][k]);
            }
            //printf("\n");
        }
        //scanning in 'o' , 'x'
        for(int j = 0;j<N;j++){
            char tempArr[50];
            scanf("%s",tempArr);
            for(int k = 0;k<M;k++){
                nono[j][k] = tempArr[k];
            }
        }
        //checking rows
        for(int j = 0;j<N && valid;j++){
            int count = 0,lastOne = 0,flag = 0;
            int compose[25];
            for(int k = 0;k<M;k++){
                if(lastOne == 1){
                    if(nono[j][k] == 'o'){
                        count++;
                    }else{
                        printf("%d %d\n",j,k);
                        compose[flag] = count;
                        count = 0;
                        flag++;
                    }
                }else{
                    if(nono[j][k] == 'o'){
                        lastOne = 1;
                        count++;
                    }
                }
                if(k == M-1 && nono[j][k]){
                    printf("%d %d\n",j,k);
                    compose[flag] = count;
                    count = 0;
                }
            }
            for(int k = 0;k<rowQuesCount[j];k++){
                printf("row: %d %d\n",compose[k],rowQues[j][k]);
                if(compose[k] != rowQues[j][k]){
                    valid = 0;
                    break;
                }
            }
        }
        //checking columns
        for(int j = 0;j<M && valid;j++){
            int count = 0,lastOne = 0,flag = 0;
            int compose[25];
            for(int k = 0;k<N;k++){
                if(lastOne == 1){
                    if(nono[k][j] == 'o'){
                        count++;
                    }else{
                        printf("%d %d\n",k,j);
                        compose[flag] = count;
                        count = 0;
                        flag++;
                    }
                }else{
                    if(nono[k][j] == 'o'){
                        lastOne = 1;
                        count++;
                    }
                }
                if(k == N-1 && nono[k][j]){
                    printf("%d %d\n",k,j);
                    compose[flag] = count;
                    count = 0;
                }
            }
            for(int k = 0;k<colQuesCount[j];k++){
                printf("col: %d %d\n",compose[k],colQues[j][k]);
                if(compose[k] != colQues[j][k]){
                    valid = 0;
                    break;
                }
            }
        }
        //print result
        if(valid){
            printf("Yes\n");
        }else{
            printf("No\n");
        }        
    }
}