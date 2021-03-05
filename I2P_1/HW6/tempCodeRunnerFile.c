#include <stdio.h>

int main(){
    int R,C,T;
    scanf("%d %d %d",&R,&C,&T);

    char classroom[R][C];

    for(int i = 0;i<R;i++){
        for(int j = 0;j<C;j++){
            scanf("%c",&classroom[i][j]);
        }
    }

    for(int i = 0;i<T;i++){
        for(int j = 0;j<R;j++){
            for(int k = 0;k<C;k++){
                if(classroom[j][k] == 'F'){
                    if(classroom[j+1][k] == 'C'){
                        classroom[j+1][k] == 'F';
                    }
                    if(classroom[j-1][k] == 'C'){
                        classroom[j+1][k] == 'F';
                    }
                    if(classroom[j][k+1] == 'C'){
                        classroom[j+1][k] == 'F';
                    }
                    if(classroom[j][k-1] == 'C'){
                        classroom[j+1][k] == 'F';
                    }
                }
            }
        }
    }

    for(int i = 0;i<R;i++){
        for(int j = 0;j<C;j++){
            printf("%c",classroom[i][j]);
        }
        printf("\n");
    }

    return 0;
}