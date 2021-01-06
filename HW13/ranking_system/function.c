#include "function.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//Add Node* with (score, name) into Table.
void Insert( Node** Table, int N, int score, char* name ){
    //printf("INS\n");
    Node* temp = (Node*)malloc(sizeof(Node));
    char* string = (char*)malloc(101*sizeof(char));
    strcpy(string,name);
    temp->name = string;
    temp->score = score;
    Table[N] = temp;
}
//Delete the Node* with name in the Table.
void Delete( Node** Table, int N, char* name ){
    //printf("DEL\n");
    int flag = 0;
    for(int i = 0;i<N;i++){
        if(flag == 0 && strcmp(Table[i]->name,name) == 0){
            free(Table[i]->name);
            free(Table[i]);
            Table[i] = NULL;
            flag = 1;
        }else if(flag == 1){
            Table[i-1] = Table[i];
        }
    }
    if(flag == 1){
        Table[N-1] = NULL;
    }
}
//Return int array contains the indices of top x Nodes in Table.
//The rank of Node* is defined below:
//  The higher score, the higher rank
//  For those with same score, ranking by their names in lexicological order.
int* Top( Node** Table, int N, int x){
    //printf("TOP\n");
    int* rank = (int*)malloc((x+1)*sizeof(int));
    for(int i = N-1;i>0;i--){
        for(int j = i;j > 0;j--){
            if(Table[j-1]->score < Table[j]->score){
                Node* temp = Table[j-1];
                Table[j-1] = Table[j];
                Table[j] = temp;
            }else if(Table[j-1]->score == Table[j]->score 
                    && strcmp(Table[j-1]->name,Table[j]->name) > 0){
                Node* temp = Table[j-1];
                Table[j-1] = Table[j];
                Table[j] = temp;
            }
        }
    }
    for(int i = 0;i<x;i++){
        rank[i] = i;
    }
    return rank;
}