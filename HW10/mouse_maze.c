#include <stdio.h>

int N,R,C;
int leastStep = __INT_MAX__,valid = 1;
int s_Row,s_Col,f_Row,f_Col;
char maze[505][505];
int walked[505][505];
int main(){
    scanf("%d",&N);
    for(int i = 0;i<N;i++){
        scanf("%d %d",&R,&C);
        for(int j = 0;j<R;j++){
            scanf("%s",maze[i]);
        }
        for(int j = 0;j<R;j++){
            for(int k = 0;k<C;k++){
                if(maze[j][k] == 'S'){
                    s_Row = j;
                    s_Col = k;
                }
                if(maze[j][k] == 'F'){
                    f_Row = j;
                    f_Col = k;
                }
            }
        }
        nextStep(s_Row,s_Col,0);

    }

}
void nextStep(int curR,int curC,int step){
    if(curR == f_Row && curC == f_Col){
        if(step < leastStep){
            leastStep = step;
        }
        return;
    }
}