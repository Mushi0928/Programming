#include <stdio.h>

int main(){
    int T;
    
    scanf("%d",&T);
    for(int i = 0;i<T;i++){
        int N,direction = 0,cursorX = 0,cursorY = -1;
        scanf("%d",&N);

        char space[N][N];
        
        for(int j = 0;j<N;j++){
            for(int k = 0;k<N;k++){
                space[j][k] = ' ';
            }
        }

        for(int j = N;j>0;j--){
            switch(direction){
                case 0:
                    for(int k = 0;k<j;k++){
                        cursorY++;
                        space[cursorX][cursorY] = '#';
                    }
                    direction = (direction+1)%4;
                    break;
                case 1:
                    for(int k = 0;k<j;k++){
                        cursorX++;
                        space[cursorX][cursorY] = '#';
                    }
                    direction = (direction+1)%4;
                    break;
                case 2:
                    for(int k = 0;k<j;k++){
                        cursorY--;
                        space[cursorX][cursorY] = '#';
                    }
                    direction = (direction+1)%4;
                    break;
                case 3:
                    for(int k = 0;k<j;k++){
                        cursorX--;
                        space[cursorX][cursorY] = '#';
                    }
                    direction = (direction+1)%4;
                    break;
            }
            
        }
        for(int j = 0;j<N;j++){
            for(int k = 0;k<N;k++){
                printf("%c",space[j][k]);
            }
            printf("\n");
        }
    }

    return 0;
}