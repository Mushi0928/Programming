#include "function.h"
#include <stdlib.h>
#include <stdio.h>
/**
BTNode* EXPR(){
    char temp;
    BTNode* node,*right;
    if(pos >= 0){
        right = FACTOR();
        if(pos >= 0){
            //EXPR ==> EXPR OP FACTOR
            temp = expr[pos];
            //printf("EXPR: %c %d\n",temp,pos);
            pos--;
            if(temp == '&' || temp == '|'){
                node = makeNode(temp);
                node->right = right;
                node->left = EXPR();
            }else{
                node = right;
            }
        }else{
            //EXPR ==> FACTOR
            node = right;
        }
    }
    //printf("EXPR returned\n");
    return node;
}
BTNode* FACTOR(){
    char temp;
    BTNode* node = NULL;
    if(pos >= 0){
        temp = expr[pos];
        //printf("FAC1: %c %d\n",temp,pos);
        pos--;
        //FACTOR ==> ID
        if(temp >= 'A' && temp <= 'D'){
            node = makeNode(temp);
        }
        //FACTOR ==> (EXPR)
        else if(temp == ')'){
            node = EXPR();
            //printf("FAC2: %c %d\n",expr[pos],pos);
            if(pos > 0 && expr[pos+1] != '('){
                printf("Dafuq??");
                freeTree(node);
            }
            
        }
    }
    //printf("FACTOR returned\n");
    return node;
}
**/
BTNode* EXPR(){ // FACTOR | EXPR OP FACTOR
    BTNode* node,*right;
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
BTNode* FACTOR(){ // ID | (EXPR)
    char temp;
    BTNode* node = NULL;
    if(pos >= 0){
        temp = expr[pos--];
        if(temp >= 'A' && temp <= 'D'){ //ID
            node = makeNode(temp);
        }else if(temp == ')'){  //(EXPR)
            node = EXPR();
            if(pos >= 0 && expr[pos+1] != '(')printf("WEED\n");
        }
    }
    return node;
}
BTNode* makeNode(char c){
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));

    for(int i = 0;i<6;i++){
        if(c == sym[i]){
            node->data = i;
            break;
        }
    }
    node->left = NULL;
    node->right = NULL;

    return node;
}