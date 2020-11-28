#include <stdio.h>

int main(){
    int N,M;
    scanf("%d %d",&N,&M);
    char tetris[N][M];
    int l_distance = 50,l_n = 50,l_m = 50;

    for(int i = 0;i<N;i++){
        for(int j = 0;j<M;j++){
            char temp;
            scanf("%c",&temp);
            if(temp == 'o'||temp == 'x'||temp == '.'){
                tetris[i][j] = temp;
            }else{
                j--;
            }
        }
    }
    for(int i = 0;i<N;i++){
        for(int j = 0;j<M;j++){
            int count = 0;
            if(tetris[i][j] == 'o'){
                for(int k = i;k<N;k++){
                    if(tetris[k][j] == 'x' || k == N-1){
                        if(count < l_distance){
                            l_n = i;
                            l_m = j;
                            l_distance = count;
                        }
                        break;
                    }
                    count++;
                }
            }
        }
    }
    //printf("%d %d %d\n",l_n,l_m,l_distance);
    char temp[N][M];
    char output[N][M];
    for(int i = 0;i<N;i++){
        for(int j = 0;j<M;j++){
            temp[i][j] = '.';
            output[i][j] = '.';
        }
    }
    for(int i = N-1;i>=0;i--){
        for(int j = 0;j<M;j++){
            if(tetris[i][j] == 'o'){
                temp[i+l_distance-1][j] = 'x';
            }
            if(tetris[i][j] == 'x'){
                temp[i][j] = 'x';
            }
        }
    }
    int flag = N-1;
    for(int i = N-1;i>=0;i--){
        int existX = 0;
        int allX = 1;
        for(int j = 0;j<M;j++){
            if(temp[i][j] == 'x'){
                existX = 1;
            }else{
                allX = 0;
            }
        }
        if(existX){
            if(allX){
                continue;
            }else{
                for(int j = 0;j<M;j++){
                    output[flag][j] = temp[i][j];
                }
                flag--;
            }
        }
    }
    for(int i = 0;i<N;i++){
        for(int j = 0;j<M;j++){
            printf("%c",output[i][j]);
        }
        printf("\n");
    }

    
    return 0;
}