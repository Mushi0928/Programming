#include <stdio.h>

int valid(int row,int col);
void nextQueen(int step);

int N = 0;
int count = 0;
int board[15][15] = { 0 };
int queens[15];
int main(){
    scanf("%d",&N);
    //for(int i = 0;i<N;i++)queens[i] = -1;
    nextQueen(0);
    printf("%d",count);
    return 0;
}
void nextQueen(int step){
    if(step == N){
        count++;
        return;
    }
    for(int i = 0;i<N;i++){
        if(valid(step,i)){
            board[step][i] = 1;
            queens[step] = i;
            nextQueen(step+1);
        }
        board[step][i] = 0;
    }
}
int valid(int row,int col){
    for(int i = 0;i<row;i++){
        if(queens[i]==col || row + col == queens[i] + i || row - col == i - queens[i])return 0;
    }
    return 1;
    
}