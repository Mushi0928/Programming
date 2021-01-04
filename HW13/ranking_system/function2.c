#include "function2.h"
#define MAX_SIZE 1000
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

// Node* Table[MAX_SIZE];
// N = number of nodes in Table

void Insert( Node** Table, int N, int score, char* name ){
    /*for(int i=0; i<N; i++){
        if(strcmp(Table[i]->name, name)==0){
            
        }
    }*/
    Node* temp = (Node*)malloc(sizeof(Node));
    char* string = (char*)malloc(sizeof(name));
    strcpy(string, name);
    Table[N] = temp;
    Table[N]->name = string;
    Table[N]->score = score;
}
void Delete( Node** Table, int N, char* name){
    int flag = 0;
    for(int i=0; i<N-1; i++){
        if(strcmp(Table[i]->name, name)==0) flag = 1;
        if(flag){
            strcpy(Table[i]->name, Table[i+1]->name);
            Table[i]->score = Table[i+1]->score;
        }
    }
    free(Table[N-1]->name);
    free(Table[N-1]);
    Table[N-1] = 0;
}
int* Top( Node** Table, int N, int x){
    int* add = (int*)malloc(x*sizeof(int));
    for(int i=0; i<N; i++){
        for(int j=i; j<N; j++){
            if(Table[i]->score < Table[j]->score){
                int temp = Table[i]->score;
                Table[i]->score = Table[j]->score;
                Table[j]->score = temp;
                char tempstr[10000] = {0};
                strcpy(tempstr, Table[i]->name);
                strcpy(Table[i]->name, Table[j]->name);
                strcpy(Table[j]->name, tempstr);
        }
        else if(Table[i]->score == Table[j]->score && strcmp(Table[i]->name, Table[j]->name)>0){
                int temp = Table[i]->score;
                Table[i]->score = Table[j]->score;
                Table[j]->score = temp;
                char tempstr[10000] = {0};
                strcpy(tempstr, Table[i]->name);
                strcpy(Table[i]->name, Table[j]->name);
                strcpy(Table[j]->name, tempstr);
        }
        }
    }
    for(int i=0; i<x; i++){
        add[i] = i;
    }
    return add;
}
