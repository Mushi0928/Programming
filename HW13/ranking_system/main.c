#include <stdio.h>
#include "function.h"
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define MAX_LEN 100
int N = 0;
Node* Table[MAX_SIZE];


int main(){
    for(int i=0; i<MAX_SIZE; i++)
        Table[i] = NULL;

    int K;
    scanf("%d", &K);

    char op[10];

    while( K-- ){
        // printf("K: %d\n", K);
        scanf("%s", op);
        if( strcmp(op, "INSERT" ) == 0 ){
            int score;
            char name[MAX_LEN+1];
            scanf("%d %s", &score, name );

            Insert(Table, N, score, name );
            N++;
        }
        else if( strcmp(op, "DELETE" ) == 0 ){
            char name[MAX_LEN+1];
            scanf("%s", name);

            Delete(Table, N, name );
            N--;
        }
        else if( strcmp(op, "TOP" ) == 0 ){
            int x;
            scanf("%d", &x);

            int* idxs = Top(Table, N, x);
            printf("Top %d:\n", x);
            for(int i=0; i<x; i++){
                printf("%d %s\n", Table[idxs[i]]->score, Table[idxs[i]]->name );
            }
            free( idxs );
        }
    }
    for(int i=0; i<MAX_SIZE; i++){
        if( Table[i] != NULL ){
            free(Table[i]->name);
            free(Table[i]);
            Table[i] = NULL;
        }
    }

    return 0;
}