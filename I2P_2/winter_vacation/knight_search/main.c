#include <stdio.h>

void findNext(int x, int y, int step);

int N;
char board[101][101] = { 0 };

int flag = 0;
char target[11] = "ICPCASIASG";

int direction[2][8] = {{ 1, 2, 2, 1,-1,-2,-2,-1},
                       { 2, 1,-1,-2,-2,-1, 1, 2}};

int main(){
    scanf("%d\n",&N);
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            scanf("%c",&(board[i][j]));
        }
    }
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            if(board[i][j] == 'I')findNext(i,j,1);
            if(flag)break;
        }
        if(flag)break;
    }
    printf("%s",flag?"YES\n":"NO\n");
}
void findNext(int x, int y, int step){
    if(flag)return;
    if(step == 11){
        flag = 1;
        return;
    }
    for(int i = 0;i<8;i++){
        int nextX = x + direction[0][i];
        int nextY = y + direction[1][i];
        if(nextX >= 0 && nextX <= N && nextY >= 0 && nextY <= N){
            if(board[nextX][nextY] == target[step])findNext(nextX,nextY,step+1);
        }
    }
}