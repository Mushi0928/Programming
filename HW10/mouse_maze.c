#include <stdio.h>

void nextStep(int curR,int curC,int step);

int N,R,C;
int leastStep = __INT_MAX__;
int s_Row,s_Col,f_Row,f_Col;    //紀錄S跟F的位置
char maze[505][505];    
int walked[505][505];   //紀錄走過的格子
int main(){
    scanf("%d",&N);    

    for(int i = 0;i<N;i++){
        scanf("%d %d",&R,&C);
        for(int j = 0;j<R;j++){    //scan maze
            scanf("%s",maze[j]);
        }
        for(int j = 0;j<R;j++){    //find S and F
            for(int k = 0;k<C;k++){
                //printf("%c",maze[j][k]);
                if(maze[j][k] == 'S'){
                    s_Row = j;
                    s_Col = k;
                }
                if(maze[j][k] == 'F'){
                    f_Row = j;
                    f_Col = k;
                }
            }
            //printf("\n");
        }
        walked[s_Row][s_Col] = 1;    //set S to walked
        nextStep(s_Row,s_Col,0);    //start recursion
        walked[s_Row][s_Col] = 0;   //set S back to not-walked
        //printf("S:%d %d F:%d %d\n",s_Row,s_Col,f_Row,f_Col);
        printf("%d\n",(leastStep == __INT_MAX__)?-1:leastStep);    //如果leastStep == int_max 代表沒有解 就print -1
        leastStep = __INT_MAX__;
    }

}
/*
    curR,curC:目前的位置
    step:步數
    Basis step:
        如果目前的位置跟F點一樣,就紀錄最小步數,然後return
    Recursive step:
        分別嘗試走上下左右四個方向，若不會超出邊界，且下一步的位置沒走過且不為'#'，就進入下個遞迴
        下個遞迴開始前將下一步的位置的walked設成1，下一步return後再設回來
        *若當前的步數已經超過(leastStep-1)，表示之後再怎麼跑步數都不會更少了，所以就不做嘗試直接return
*/
void nextStep(int curR,int curC,int step){
    printf("curR:%4d curC:%d step:%4d\n",curR,curC,step);
    if(curR == f_Row && curC == f_Col){
        if(step < leastStep){
            leastStep = step;
        }
    }else if(step<leastStep-1){
        if(curR > 0){
            if(maze[curR-1][curC] != '#' && !walked[curR-1][curC]){
                walked[curR-1][curC] = 1;
                nextStep(curR-1,curC,step+1);
                walked[curR-1][curC] = 0;
            }
        }
        if(curR < R-1){
            if(maze[curR+1][curC] != '#' && !walked[curR+1][curC]){
                walked[curR+1][curC] = 1;
                nextStep(curR+1,curC,step+1);
                walked[curR+1][curC] = 0;
            }
        }
        if(curC > 0){
            if(maze[curR][curC-1] != '#' && !walked[curR][curC-1]){
                walked[curR][curC-1] = 1;
                nextStep(curR,curC-1,step+1);
                walked[curR][curC-1] = 0;
            }
        }
        if(curC < C-1){
            if(maze[curR][curC+1] != '#' && !walked[curR][curC+1]){
                walked[curR][curC+1] = 1;
                nextStep(curR,curC+1,step+1);
                walked[curR][curC+1] = 0;
            }
        }
    }

}