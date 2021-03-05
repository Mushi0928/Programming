#include "function.h"
#include <stdlib.h>

void createLinkedList(Node **head, int N, int *arr){
    *head = (Node*)malloc(sizeof(Node));
    Node* temp = *head;
    (*head)->val = arr[1];
    for(int i = 2;i <= N;i++){
        Node* new = (Node*)malloc(sizeof(Node));
        temp->next = new;
        new->val = arr[i];
        temp = temp->next;
    }
    temp->next = *head;
}
void swapTwoSegment(Node **head, int a, int b, int len){
    Node* head_A;
    Node* head_B;
    Node* temp = *head;
    for(int i = 1;i <= (a>b?a:b);i++){
        if(i == a)head_A = temp;
        if(i == b)head_B = temp;
        temp = temp->next;
    }
    for(int i = 0;i<len;i++){
        int tempVal = head_A->val;
        head_A->val = head_B->val;
        head_B->val = tempVal;
        head_A = head_A->next;
        head_B = head_B->next;
    }
}