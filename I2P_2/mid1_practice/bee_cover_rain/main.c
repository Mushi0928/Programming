#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    unsigned long long data;
    struct node* left;
    struct node* right;
}Node;

Node* makeTree();
unsigned long long calculate(Node* root);
void printTree(Node* root);

int p,q;
int idx,str_len;
char str[5000001];
Node* root;

int main(){
    scanf("%d %d",&p,&q);
    scanf("%s",str);
    p %= q;
    root = makeTree();
    printf("%llu\n",calculate(root));
    //printTree(root);
    return 0;
}
Node* makeTree(){
    Node* node = (Node*)malloc(sizeof(Node));
    if(str[idx] == 'f'){
        node->data = -1;    //indicates f
        idx += 2;   //scanned "f("
        node->left = makeTree();
        idx += 1;   //scanned ","
        node->right = makeTree();
        idx += 1;   //scanned ")"
    }else{
        unsigned long long sum = str[idx++] - '0';
        while(str[idx] >= '0' && str[idx] <= '9'){
            sum = sum*10 + str[idx] - '0';
            idx++;
        }
        node->data = sum % q;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}
unsigned long long calculate(Node* root){
    if(root->data == -1){
        unsigned long long px = p * calculate(root->left);
        return (((px!=0)?px%q:0) + calculate(root->right))%q;
    }else{
        return root->data;
    }
}
void printTree(Node* root){
    if(root->data == -1){
        printf("f(");
        printTree(root->left);
        printf(",");
        printTree(root->right);
        printf(")");
    }else{
        printf("%d",root->data);
    }
}