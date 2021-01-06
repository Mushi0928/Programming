#include "function.h"
void Push(Node** ptr_head, int x){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = x;
    temp->next = *ptr_head;   
    *ptr_head = temp;
}
void Pop(Node** ptr_head){
    if(*ptr_head != NULL){
        Node* temp = *ptr_head;
        *ptr_head = (*ptr_head)->next;
        free(temp);
    }
}
void Reverse_List(Node** ptr_head){
    if(*ptr_head == NULL)return;
    Node* temp = *ptr_head;
    int count = 0;
    while(temp->next != NULL){
        count++;
        temp = temp->next;
    }
    temp = *ptr_head;
    Node* ptr[count];
    for(int i = 0;i<count;i++){
        ptr[i] = temp;
        temp = temp->next;
    }
    Node* new_head = temp;
    for(int i = count-1;i >= 0;i--){
        temp->next = ptr[i];
        temp = temp->next;
    }
    temp->next = NULL;
    *ptr_head = new_head;
}