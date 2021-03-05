#include <stdio.h>
#include <stdlib.h>

void insert(char character);
void backspace();
void print();

int T,N;

typedef struct node{
    char character;
    struct node* prev;
    struct node* next;
}Node;

Node* cursor;
Node head;
Node tail;

int main(){
    scanf("%d",&T);
    head.character = '\0';
    head.prev = NULL;
    head.next = &tail;
    tail.character = '\0';
    tail.prev = &head;
    tail.next = NULL;
    while(T--){
        scanf("%d\n",&N);
        char temp;
        cursor = &head;
        head.next = &tail;
        tail.prev = &head;
        while(N--){
            scanf("%c",&temp);
            if(temp == 'L'){
                if(cursor->prev != NULL)cursor = cursor->prev;
            }else if(temp == 'R'){
                if(cursor->next != &tail)cursor = cursor->next;
            }else if(temp == 'B'){
                backspace();
            }else{
                insert(temp);
            }
        }
        print();
    }
}
void insert(char character){
    Node* new = (Node*)malloc(sizeof(Node));
    new->character = character;
    new->prev = cursor;
    new->next = cursor->next;
    (new->next)->prev = new;
    cursor->next = new;
    cursor = cursor->next;
}
void backspace(){
    if(cursor == &head)return;
    Node* deleted = cursor;
    cursor = cursor->prev;
    cursor->next = deleted->next;
    (deleted->next)->prev = cursor;
    free(deleted);
}
void print(){
    Node* temp = head.next;
    while(temp != &tail){
        printf("%c",temp->character);
        temp = temp->next;
        free(temp->prev);
    }
    printf("\n");
}