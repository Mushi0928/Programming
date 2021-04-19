#include "function.h"
#include <stdlib.h>
#include <stdio.h>

void printInfix(Node *root){
    //left
    if(root->left != NULL){
        char left = (root->left)->data;
        //if((left == '|' || left == '&') && left != root->data)printf("(");
        printInfix(root->left);
        //if((left == '|' || left == '&') && left != root->data)printf(")");
    }
    //root
    printf("%c",root->data);
    //right
    if(root->right != NULL){
        char right = (root->right)->data;
        if((right == '|' || right == '&') /** && right != root->data **/)printf("(");
        printInfix(root->right);
        if((right == '|' || right == '&') /** && right != root->data **/)printf(")");
    }
}