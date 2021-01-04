#include "function.h"
void Push(Node** ptr_head, int x){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = x;
    if(*ptr_head != NULL){
        temp->next = *ptr_head;   
    }
    *ptr_head = temp;
}
void Pop(Node** ptr_head){
    Node* temp = *ptr_head;
    *ptr_head = (*ptr_head)->next;
    free(temp);
}
void Reverse_List(Node** ptr_head){
    static Node* head = NULL;
    if((*ptr_head)->next == NULL){
        head = *ptr_head;
    }else{
        Reverse_List(&((*ptr_head)->next)));
        
    }
}