#include <stdio.h>
#include <math.h>

int main(){
    int N;
    int matrix[20][20];

    scanf("%d",&N);
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            scanf("%d",&matrix[i][j]);
        }
    }
    for(int i = 0;i<N;i++){
        for(int j = 0;j < (i+1);j++){
            if(j != 0)printf(" ");
            printf("%d",matrix[i-j][j]);
        }
        printf("\n");
    }
    for(int i = 0;i<(N-1);i++){
        for(int j = 0;j<(N-1-i);j++){
            if(j != 0)printf(" ");
            //printf("%d",j);
            printf("%d",matrix[N-1-j][i+j+1]);
        }
        printf("\n");
    }
    return 0;
}