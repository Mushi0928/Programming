#include "function.h"
#include <stdio.h>
#include <stdlib.h>
Node* ReadOneList(){
    Node* temp = (Node*)malloc(sizeof(Node));
    int num_count;
    scanf("%d:",&num_count);

    int* numbers = (int*)malloc(num_count * sizeof(int));
    for(int i = 0;i<num_count;i++){
        scanf("%d",&(numbers[i]));
    }
    temp->size = num_count;
    temp->data = numbers;
    temp->next = NULL;

    return temp;
}
void PrintList(Node* head){
    Node* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
        for(int i = 0;i<temp->size - 1;i++){
            printf("%d ",(temp->data)[i]);
        }
        printf("%d\n",(temp->data)[temp->size - 1]);
    }
}
void Merge(Node* head, int x, int y){
    Node* node_x;
    Node* node_y;
    Node* node_x_prev;
    Node* temp = head;
    for(int i = 0;i<=(x>y?x:y);i++){
        if(i == x)node_x = temp;
        if(i == y)node_y = temp;
        if(i == x-1)node_x_prev = temp;
        temp = temp->next;
    }

    int* new_data = (int*)malloc((node_x->size + node_y->size)*sizeof(int));
    for(int i = 0;i<node_y->size;i++){
        new_data[i] = (node_y->data)[i];
    }
    for(int i = 0;i<node_x->size;i++){
        new_data[i + node_y->size] = (node_x->data)[i];
    }

    free(node_y->data);
    node_y->data = new_data;
    node_y->size = node_x->size + node_y->size;
    node_x_prev->next = node_x->next;
    free(node_x->data);
    free(node_x);

}
void Cut(Node* head, int x, int u){
    Node* node_x = head;
    Node* node_y = (Node*)malloc(sizeof(Node));
    for(int i = 0;i<x;i++){
        node_x = node_x->next;
    }
    int* new_data_x = (int*)malloc(u * sizeof(int));
    int* new_data_y = (int*)malloc((node_x->size - u) * sizeof(int));
    for(int i = 0;i<u;i++){
        new_data_x[i] = (node_x->data)[i];
    }
    for(int i = 0;i<(node_x->size - u);i++){
        new_data_y[i] = (node_x->data)[u+i];
    }
    node_y->data = new_data_y;
    node_y->next = node_x->next;
    node_y->size = (node_x->size - u);

    free(node_x->data);
    node_x->data = new_data_x;
    node_x->next = node_y;
    node_x->size = u;
}