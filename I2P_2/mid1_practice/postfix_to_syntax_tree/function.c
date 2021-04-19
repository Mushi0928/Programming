#include <stdlib.h>
#include <string.h>
#include "function.h"

void constructTree(Node** head){
    if(idx >= strlen(s1))return;
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = s2[idx++];
    if(node->data == '|' || node->data == '&'){
        constructTree(&(node->right));
        constructTree(&(node->left));
    }else{
        node->left = NULL;
        node->right = NULL;
    }
    *head = node;
}
