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
        char nono[N][M];

        //scanning in questions
        for(int j = 0;j<N;j++){
            int numCount;
            scanf("%d",&numCount);
            for(int k = 0;k<numCount;k++){
                scanf("%d",&rowQues[j][k]);
                //printf("%d ",rowQues[j][k]);
            }
            //printf("\n");
        }
        for(int j = 0;j<M;j++){
            int numCount;
            scanf("%d",&numCount);
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
        for(int j = 0;j<N;j++){
            int count = 0;
            int flag = 0;
            int lastOne;
            if(nono[j][0] == 'o'){
                lastOne = 1;
                count++;
            }else{
                lastOne = 0;
            }
            for(int k = 1;k<M && valid;k++){
                if(nono[j][k] == 'o'){
                    if(lastOne == 1){
                        count++;
                    }else{
                        lastOne = 1;
                        count++;
                    }
                }else{
                    if(lastOne == 1){
                        printf("row: %d %d   %d %d\n",count,rowQues[j][flag],j,k);
                        if(count != rowQues[j][flag]){
                            valid = 0;
                            break;
                        }else{
                            flag++;
                        }
                        lastOne = 0;
                        count = 0;
                    }
                }
                if(k == M-1){
                    if(count != rowQues[j][flag]){
                        valid = 0;
                        break;
                    }else{
                        flag++;
                    }
                    lastOne = 0;
                    count = 0;
                }
            }
        }
        //checking columns
        for(int j = 0;j<M;j++){
            int count = 0;
            int flag = 0;
            int lastOne;
            if(nono[0][j] == 'o'){
                lastOne = 1;
                count++;
            }else{
                lastOne = 0;
            }
            for(int k = 1;k<N && valid;k++){
                if(nono[k][j] == 'o'){
                    if(lastOne == 1){
                        count++;
                    }else{
                        lastOne = 1;
                        count++;
                    }
                }else{
                    if(lastOne == 1){
                        printf("col: %d %d   %d %d\n",count,colQues[j][flag],j,k);
                        if(count != colQues[j][flag]){
                            valid = 0;
                            break;
                        }else{
                            flag++;
                        }
                        lastOne = 0;
                        count = 0;
                    }
                }
                if(k == N-1){
                    if(count != colQues[j][flag]){
                        valid = 0;
                        break;
                    }else{
                        flag++;
                    }
                    lastOne = 0;
                    count = 0;
                }
            }
        }
        if(valid){
            printf("Yes\n");
        }else{
            printf("No\n");
        }        
    }
}