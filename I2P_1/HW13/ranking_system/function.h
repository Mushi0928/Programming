// function.h
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

typedef struct{
    int score;
    char* name;
} Node;

// Node* Table[MAX_SIZE];
// N = number of nodes in Table
 
void Insert( Node** Table, int N, int score, char* name );
void Delete( Node** Table, int N, char* name );
int* Top( Node** Table, int N, int x);
#endif