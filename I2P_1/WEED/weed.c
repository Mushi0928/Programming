#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char plays[3][10] = {"Scissor","Rock","Paper"};

int duel(int a,int b){
    if(a == b){
        return 2;
    }
    if(a == 0 && b == 1){
        return 0;
    }
    if(a == 0 && b == 2){
        return 1;
    }
    if(a == 1 && b == 0){
        return 1;
    }
    if(a == 1 && b == 2){
        return 0;
    }
    if(a == 2 && b == 0){
        return 0;
    }
    if(a == 2 && b == 1){
        return 1;
    }
    return 0;
}

int main(){
    char player_play;
    int WL = 0;
    int com;
    srand(time(NULL));
    com = rand()%3;
    //printf("%d",com);
    int player = 0;
    printf("\nRock ,Paper ,Scissor : ");
    scanf("%c",&player_play);
    if(player_play == 'p'){
        player = 2;
    }else if(player_play == 's'){
        player = 0;
    }else{
        player = 1;
    }
    //printf("a");
    WL = duel(player,com);
    //printf("b");
    if(WL == 0){
        printf("\nThe opponent played %s and you played %s.\nYou lose ~\n\n\n",plays[com],plays[player]);
    }else if(WL == 1){
        printf("\nThe opponent played %s and you played %s.\nYou win ~\n\n\n",plays[com],plays[player]);
    }else{
        printf("\nThe opponent played %s and you played %s.\nIt's a draw ~\n\n\n",plays[com],plays[player]);
    }
    //printf("c");
    return 0;
}