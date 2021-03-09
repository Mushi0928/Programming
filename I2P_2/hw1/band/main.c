#include <stdio.h>
#include <stdlib.h>

typedef struct group{
    char* text;
    struct group* next;
}Group;

typedef struct row{
    Group* head;
    Group* tail;
}Row;

Group* createGroup(int size);
void moveToHead(int from,int to);
void moveToTail(int from,int to);
void swapRow(int a,int b);

int N,Q;

Row row[100001];
int main(){
    scanf("%d",&N);
    int size;
    for(int i = 1;i<=N;i++){
        scanf("%d",&size);
        if(size > 0){
            row[i].head = createGroup(size);
            row[i].tail = row[i].head;
        }else{
            row[i].head = NULL;
            row[i].tail = NULL;
        }
    }
    scanf("%d",&Q);
    int type,from,to; 
    while(Q--){
        scanf("%d %d %d",&type,&from,&to);
        switch(type){
            case 1:
                moveToHead(from,to);
                break;
            case 2:
                moveToTail(from,to);
                break;
            case 3:
                swapRow(from,to);
                break;
            default:
                break;
        }
    }
    for(int i = 1;i<=N;i++){
        if(row[i].head != NULL){
            Group* temp = row[i].head;
            while(temp != NULL){
                printf("%s",temp->text);
                temp = temp->next;
            }
        }
        printf("\n");
    }
}

Group* createGroup(int size){
    Group* new_group = (Group*)malloc(sizeof(Group));
    char* text = (char*)malloc((size+1) * sizeof(char));
    scanf("%s",text);
    new_group->text = text;
    new_group->next = NULL;
    return new_group;
}
void moveToHead(int from,int to){
    if(row[from].head == NULL)return;
    if(row[to].head == NULL){
        row[to].head = row[from].head;
        row[to].tail = row[from].tail;
        row[from].head = NULL;
        row[from].tail = NULL;
    }else{
        row[from].tail->next = row[to].head;
        row[to].head = row[from].head;
        row[from].head = NULL;
        row[from].tail = NULL;
    }
}
void moveToTail(int from,int to){
    if(row[from].head == NULL)return;
    if(row[to].tail == NULL){
        row[to].head = row[from].head;
        row[to].tail = row[from].tail;
        row[from].head = NULL;
        row[from].tail = NULL;
    }else{
        row[to].tail->next = row[from].head;
        row[to].tail = row[from].tail;
        row[from].head = NULL;
        row[from].tail = NULL;
    }
}
void swapRow(int a,int b){
    Group* a_head = row[a].head;
    Group* a_tail = row[a].tail;

    row[a].head = row[b].head;
    row[a].tail = row[b].tail;

    row[b].head = a_head;
    row[b].tail = a_tail;
}