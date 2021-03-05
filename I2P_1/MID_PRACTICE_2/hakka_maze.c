#include <stdio.h>

void nextStep(int curN,int curM);

int T,N,M;
int end_N,end_M;
int valid = 0;
int teleported = 0;
int walked[1005][1005];
char maze[1005][1005];
int portal[1000000][2];
int portalCursor = 0;

int main(){
    scanf("%d",&T);
    for(int i = 0;i<T;i++){
        scanf("%d %d",&N,&M);
        for(int j = 0;j<N;j++){
            scanf("%s",maze[j]);
        }
        for(int j = 0;j<N;j++){
            for(int k = 0;k<M;k++){
                if(maze[j][k] == 'T'){
                    portal[portalCursor][0] = j;
                    portal[portalCursor][1] = k;
                    portalCursor++;
                }
                //printf("%c",maze[j][k]);
            }
            //printf("\n");
        }
        end_N = N-1;
        end_M = M-1;
        walked[0][0] = 1;
        nextStep(0,0);
        printf("%s\n",(valid)?"Yes":"No");
        portalCursor = 0;
        valid = 0;
    }
    return 0;
}
void nextStep(int curN,int curM){
    if(valid == 1 || (curN == end_N && curM == end_M)){
        //printf("N:%3d M:%3d\n",curN,curM);
        valid = 1;
        return;
    }else{
        //printf("N:%3d M:%3d\n",curN,curM);
        if(maze[curN][curM] == 'T' && !teleported){
            teleported = 1;
            for(int i = 0;i<portalCursor;i++){
                if(!walked[portal[i][0]][portal[i][1]]){
                    walked[portal[i][0]][portal[i][1]] = 1;
                    nextStep(portal[i][0],portal[i][1]);
                    walked[portal[i][0]][portal[i][1]] = 0;
                }
            }
        }
        if(curN > 0){
            if(maze[curN-1][curM] != '#' && !walked[curN-1][curM]){
                walked[curN-1][curM] = 1;
                nextStep(curN-1,curM);
                walked[curN-1][curM] = 0;
            }
        }
        if(curN < N-1){
            if(maze[curN+1][curM] != '#' && !walked[curN+1][curM]){
                walked[curN+1][curM] = 1;
                nextStep(curN+1,curM);
                walked[curN+1][curM] = 0;
            }
        }
        if(curM > 0){
            if(maze[curN][curM-1] != '#' && !walked[curN][curM-1]){
                walked[curN][curM-1] = 1;
                nextStep(curN,curM-1);
                walked[curN][curM-1] = 0;
            }
        }
        if(curM < M-1){
            if(maze[curN][curM+1] != '#' && !walked[curN][curM+1]){
                walked[curN][curM+1] = 1;
                nextStep(curN,curM+1);
                walked[curN][curM+1] = 0;
            }
        }
    }   
}