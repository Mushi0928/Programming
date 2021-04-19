#include <stdlib.h>
#include <stdio.h>
#include "function.h"

void freeNode(struct Node* n);

struct Graph* createGraph(int vertices_num){
    struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph*));
    struct Node** adjList = (struct Node**)malloc(vertices_num * sizeof(struct Node*));
    
    for(int i = 0;i < vertices_num;i++){
        adjList[i] = NULL;
    }
    g->vertices_num = vertices_num;
    g->adjLists = adjList;
    //printf("graph create\n");
    return g;
}
void addEdge(struct Graph* g, int u, int v){
    struct Node* u_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* v_node = (struct Node*)malloc(sizeof(struct Node));
    u_node->id = u;
    u_node->next = NULL;
    v_node->id = v;
    v_node->next = NULL;
    if((g->adjLists)[u] != NULL)v_node->next = (g->adjLists)[u];
    g->adjLists[u] = v_node;
    if((g->adjLists)[v] != NULL)u_node->next = (g->adjLists)[v];
    g->adjLists[v] = u_node;
}
int findMax(struct Graph* g, int now , int prev){
    int max = now;
    for(struct Node* temp = (g->adjLists)[now];temp != NULL;temp = temp->next){
        if(temp->id == prev)continue;
        int new = findMax(g,temp->id,now);
        if(max < new)max = new;
    }
    return max;
}
void freeGraph(struct Graph* g){
    for(int i = 0;i < g->vertices_num;i++){
        freeNode((g->adjLists)[i]);
    }
    free(g->adjLists);
    free(g);
    //printf("finished free\n");
}
void freeNode(struct Node* n){
    if(n == NULL)return;
    if(n->next != NULL)freeNode(n->next);
    free(n);
}