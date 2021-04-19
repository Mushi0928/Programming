#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    int partial_sum_set;
    struct node* left;
    struct node* right;    
}Node;

int N;
int idx = 0;
int min = __INT_MAX__;
char str[300001];
Node* root;

Node* makeTree();
Node* spinRight(Node* root);
Node* spinLeft(Node* root);
void calculate(Node* node);

int main(){
    scanf("%d",&N);
    scanf("%s",str);
    root = makeTree();
    //if(root->partial_sum_set < min)min = root->partial_sum_set;
    min = root->partial_sum_set;
    root = spinRight(root);
    spinLeft(root);
    printf("%d\n",min);
    return 0;
}
Node* makeTree(){
    if(idx >= N)return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    int temp = str[idx++];
    switch(temp){   // + => -1  - => -2  * => -3
        case '0' ... '9':
            node->data = temp - '0';
            node->left = NULL;
            node->right = NULL;
            calculate(node);
            break;
        case '+':
            node->data = -1;
            node->left = makeTree();
            node->right = makeTree();
            calculate(node);
            break;
        case '-':
            node->data = -2;
            node->left = makeTree();
            node->right = makeTree();
            calculate(node);
            break;
        case '*':
            node->data = -3;
            node->left = makeTree();
            node->right = makeTree();
            calculate(node);
            break;
    }
    return node;
}
Node* spinRight(Node* root){
    if((root->left)->data >= 0)return root;
    Node* new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    calculate(new_root->right);
    calculate(new_root);
    if(new_root->partial_sum_set < min)min = new_root->partial_sum_set;
    //printf("%d\n", new_root->partial_sum_set);
    return spinRight(new_root);
}
Node* spinLeft(Node* root){
    if((root->right)->data >= 0)return root;
    Node* new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    calculate(new_root->left);
    calculate(new_root);
    if(new_root->partial_sum_set < min)min = new_root->partial_sum_set;
    //printf("%d\n", new_root->partial_sum_set);
    return spinLeft(new_root);
}
void calculate(Node* node){
    switch(node->data){   // + => -1  - => -2  * => -3
        case 0 ... 9:
            node->partial_sum_set = node->data;
            break;
        case -1:
            node->partial_sum_set = (node->left)->partial_sum_set + (node->right)->partial_sum_set;
            break;
        case -2:
            node->partial_sum_set = (node->left)->partial_sum_set - (node->right)->partial_sum_set; 
            break;
        case -3:
            node->partial_sum_set = (node->left)->partial_sum_set * (node->right)->partial_sum_set;
            break;
    }
    //printf("node: %d partial sum: %d\n",node->data,node->partial_sum_set);
}