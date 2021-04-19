#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}Node;

int N;
Node* tree;
int root_idx;

void check(Node* node,int boundary_L,int boundary_R);
void pruneLeaf(Node* node);

int main(){
    scanf("%d",&N);
    tree = (Node*)malloc(N * sizeof(Node));

    for(int i = 0;i<N;i++){
        scanf("%d",&(tree[i].data));
        tree[i].left = NULL;
        tree[i].right = NULL;
    }

    int temp_num;
    char temp_char;
    for(int i = 0;i<N;i++){
        scanf("%d",&temp_num);
        if(temp_num == 0){
            root_idx = i;
            continue;
        }else{
            scanf("%c",&temp_char);
            if(temp_char == 'L'){
                tree[temp_num-1].left = tree + i;
            }else{
                tree[temp_num-1].right = tree + i;
            }
        }
    }

    check(tree + root_idx,__INT_MAX__ * -1,__INT_MAX__);

    for(int i = 0;i<N;i++){
        if(i != 0)printf(" ");
        printf("%d",tree[i].data);
    }
    printf("\n");
    return 0;
}
void check(Node* node,int boundary_L,int boundary_R){
    if(node == NULL)return;
    if(node->data > boundary_L && node->data < boundary_R){
        check(node->left,boundary_L,node->data);
        check(node->right,node->data,boundary_R);
    }else{
        pruneLeaf(node);
    }
}
void pruneLeaf(Node* node){
    if(node == NULL)return;
    int new_value = 0;
    if(node->left != NULL){
        pruneLeaf(node->left);
        if((node->left)->data < new_value)new_value = (node->left)->data;
    }
    if(node->right != NULL){
        pruneLeaf(node->right);
        if((node->right)->data < new_value)new_value = (node->right)->data;
    }
    node->data = new_value - 1;
}
