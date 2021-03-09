#include <stdio.h>
#include <stdlib.h>

int t = 0, n = 0;

typedef struct _node{
    char letter;
    struct _node* next;
    struct _node* prev;
} Node;

int main(void){
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        Node string[n+1];
        Node headori;
        Node* head = &headori;
        Node* temp = head;
        head->prev = NULL;
        head->next = NULL;
        for(int i=0; i<n; i++){
            char input = 0;
            scanf(" %c", &input);
            if(input=='B'){
                if(temp->prev!=head){
                    if(temp->next!=NULL){
                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;
                    } else{
                        temp->prev->next = NULL;
                    }
                    temp = temp->prev;
                } else{
                    if(temp->next!=NULL) temp = temp->next;
                    else{
                        temp = head;
                        head->next = NULL;
                    }
                }
            } else if(input=='L'){
                if(temp->prev!=head) temp = temp->prev; 
                else temp = head;
            } else if(input=='R'){
                if(temp->next!=NULL) temp = temp->next;
            } else{
                string[i].letter = input;
                Node* add = &string[i];
                if(temp->next!=NULL){
                    Node* ori = temp->next;
                    temp->next = add;
                    add->next = ori;
                    add->prev = temp;
                    ori->prev = temp->next;
                } else{
                    temp->next = add;
                    add->prev = temp;
                    add->next = NULL;
                }
                temp = add;
            }
        }
        temp = head->next;
        while(temp!=NULL){
            printf("%c", temp->letter);
            temp = temp->next;
        }
        printf("\n");
    }
    return 0;
}