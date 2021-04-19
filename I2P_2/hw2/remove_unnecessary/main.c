#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char data;
    struct node *left,*right;
}Node;

Node* EXPR();
Node* FACTOR();
Node* makeNode(char data);
void printInfix(Node* root);

Node* root;
char expr[256];
int pos;

int main(){
    scanf("%s",expr);
    pos = strlen(expr) - 1;
    root = EXPR();
    printInfix(root);
    //printf("\n");
}
Node* EXPR(){ // FACTOR | EXPR OP FACTOR
    Node* node,*right;
    char temp;
    if(pos >= 0){
        node = FACTOR(); //FACTOR
        if(pos >= 0){
            temp = expr[pos--];
            if(temp == '|' || temp == '&'){ //EXPR OP FACTOR
                right = node;
                node = makeNode(temp);
                node->right = right;
                node->left = EXPR();
            }
        }
    }
    return node;
}
Node* FACTOR(){ // ID | (EXPR)
    char temp;
    Node* node;
    if(pos >= 0){
        temp = expr[pos--];
        if(temp >= 'A' && temp <= 'D'){ //ID
            node = makeNode(temp);
        }else if(temp == ')'){
            node = EXPR();
            if(pos >= 0 && expr[pos+1] != '(')printf("WEED\n");
        }
    }
    return node;
}
Node* makeNode(char data){
    Node* node = (Node*)malloc(sizeof(Node));

    node->left = NULL;
    node->right = NULL;
    node->data = data;

    return node;
}
void printInfix(Node* root){
    //left
    if(root->left != NULL)printInfix(root->left);
    //root
    printf("%c",root->data);
    //right
    if(root->right != NULL){
        char right = (root->right)->data;
        if(right == '|' || right == '&')printf("(");
        printInfix(root->right);
        if(right == '|' || right == '&')printf(")");
    }
}

