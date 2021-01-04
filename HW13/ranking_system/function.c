#include "function.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//Add Node* with (score, name) into Table.
void Insert( Node** Table, int N, int score, char* name ){
    //printf("INS\n");
    Node* temp = (Node*)malloc(sizeof(Node));
    char* string = (char*)malloc(100*sizeof(char));
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
}
//Return int array contains the indices of top x Nodes in Table.
//The rank of Node* is defined below:
//  The higher score, the higher rank
//  For those with same score, ranking by their names in lexicological order.
int* Top( Node** Table, int N, int x){
    //printf("TOP\n");
    int* rank = (int*)malloc((N+1)*sizeof(int));
    for(int i = N-1;i>0;i--){
        for(int j = 0;j < i;j++){
            if(Table[j]->score < Table[j+1]->score){
                Node* temp = Table[j];
                Table[j] = Table[j+1];
                Table[j+1] = temp;
            }else if(Table[j]->score == Table[j+1]->score 
                    && strcmp(Table[j]->name,Table[j+1]->name) > 0){
                Node* temp = Table[j];
                Table[j] = Table[j+1];
                Table[j+1] = temp;
            }
        }
    }
    for(int i = 0;i<x;i++){
        rank[i] = i;
    }
    return rank;
}