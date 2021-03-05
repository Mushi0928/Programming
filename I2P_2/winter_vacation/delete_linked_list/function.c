#include "function.h"

void deleteNode(Node ** nd, int data){
    Node* temp = *nd;
    for(int i = 0;i < data-2;i++){
        if(temp->next == NULL)return;
        temp = temp->next;
    }
    if(temp->next != NULL){
        if(data == 1){
            (*nd) = (*nd)->next;
            free(temp);
            return;
        }
        Node* deleted = temp->next;
        temp->next = deleted->next;
        free(deleted);
    }
}

Node* createList(){
    int tempData;
    Node* head;
    Node* flag;
    head = (Node*)malloc(sizeof(Node));
    scanf("%d",&(head->data));
    head->next = NULL;
    flag = head;
    while(1){
        scanf("%d",&tempData);
        if(tempData > -1){
            Node* temp = (Node*)malloc(sizeof(Node));
            temp->data = tempData;
            temp->next = NULL;
            flag->next = temp;
            flag = temp;
        }else break;
    }
    return head;
}