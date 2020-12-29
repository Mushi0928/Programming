#include <stdio.h>

void DFS(int curX,int curY);

int T,N,M;
int visited[1005][1005];
char map[1005][1005];
int teleport = 0;

int main(){

    scanf("%d",&T);
    
    for(int i = 0;i<T;i++){
        scanf("%d %d",&N,&M);
        for(int j = 0;j<N;j++){
            scanf("%s",map[j]);
            for(int k = 0;k<M;k++){
                visited[j][k] = 0;
            }
        }
        DFS(0,0);
        if(visited[N-1][M-1]){
            printf("Yes\n");
            continue;
        }
        for(int j = 0;j<N;j++){
            for(int k = 0;k<M;k++){
                if(map[j][k] == 'T'){
                    DFS(j,k);
                }
            }
        }
        if(visited[N-1][M-1]){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
        teleport = 0;
    }
    return 0;
}
void DFS(int curX,int curY){
    //printf("%4d %4d\n",curX,curY);
    if(visited[curX][curY]){
        return;
    }else if(map[curX][curY] == 'T'){
        teleport = 1;
    }
    visited[curX][curY] = 1;
    if(curX>0 && map[curX-1][curY] != '#'){
        //visited[curX-1][curY] = 1;
        DFS(curX-1,curY);
    }
    if(curX<N-1 && map[curX+1][curY] != '#'){
        //visited[curX+1][curY] = 1;
        DFS(curX+1,curY);
    }
    if(curY>0 && map[curX][curY-1] != '#'){
        //visited[curX][curY-1] = 1;
        DFS(curX,curY-1);
    }
    if(curY<M-1 && map[curX][curY+1] != '#'){
        //visited[curX][curY+1] = 1;
        DFS(curX,curY+1);
    }
}