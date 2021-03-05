#include <stdio.h>
char y[3] = {'A','B','C'};
void printBoard(char a[3][3]){
    printf("\n  1 2 3\n");
    for(int i = 0;i<3;i++){
        printf("%c ",y[i]);
        for(int j = 0;j<3;j++){
            printf("%c ",a[i][j]);
        }
        printf("\n");
    }
}
int check(char a[3][3]){
    char result = 'n';
    for(int i = 0;i<3;i++){
        if(a[i][0]==a[i][1] && a[i][1]==a[i][2] &&(a[i][0]=='o' || a[i][0]=='x'))result = a[i][0];
        if(a[0][i]==a[1][i] && a[1][i]==a[2][i] &&(a[i][0]=='o' || a[i][0]=='x'))result = a[0][i];
    }
    if(a[0][0]==a[1][1] && a[1][1]==a[2][2] &&(a[0][0]=='o' || a[0][0]=='x'))result = a[0][0];
    if(a[2][0]==a[1][1] && a[1][1]==a[0][2] &&(a[2][0]=='o' || a[2][0]=='x'))result = a[2][0];
    return result;
}
void announce_winner(int winner){

}
int main(){
    int game_running = 1,round = 1;
    char gameboard[3][3] = {{'-','-','-'},{'-','-','-'},{'-','-','-'}};
    printBoard(gameboard);
    do{
        int x;
        char y;
        printf("Player 1's turn : ");
        scanf("%c %d",&y,&x);
        gameboard[y-65][x-1] = 'o';
        printf("pb");
        printBoard(gameboard);
        /*
        if(check(gameboard)=='o'){
            printf("Player 1 wins ~");
            game_running = 0;
            continue;
        }
        */
        int a;
        char b;
        printf("Player 2's turn : ");
        scanf("%c %d",&b,&a);
        gameboard[b-65][a-1] = 'x';
        printBoard(gameboard);
        /*
        if(check(gameboard)=='x'){
            printf("Player 2 wins ~");
            game_running = 0;
            continue;
        }
        */
    }while(game_running);
}