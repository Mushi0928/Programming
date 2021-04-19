#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *left,*right;
}Node;

void binaryTree(Node* root,int num);
Node* makeNode(int data);
void printTree(Node* root);
Node* BST(int start,int end);

int nums[200000];
int numCount = 0;
int pos = 0;
Node* root;
int main(){
    char temp;
    int a;
    while(scanf("%d",nums+numCount) != EOF){
        numCount++;
        //scanf("%c",&temp);
        //if(temp == '\n')break;
    }
    root = BST(0,numCount - 1);
    //root = makeNode(nums[numCount - 1]);
    /**
    for(int i = numCount - 2;i >= 0;i--){
        binaryTree(root,nums[i]);
    }
    **/
    //printTree(root);
    /**
    for(int i = 0;i<numCount-1;i++){
        printf("%d ",nums[i]);
    }
    
    printf("%d\n",nums[numCount - 1]);
    **/
    return 0;
}
void binaryTree(Node* root,int num){
    //printf("%d\n",num);
    if(num > root->data){
        if(root->right == NULL){
            root->right = makeNode(num);
        }else{
            binaryTree(root->right,num);
        }
    }else{
        if(root->left == NULL){
            root->left = makeNode(num);
        }else{
            binaryTree(root->left,num);
        }
    }
}
Node* makeNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}
Node* BST(int start,int end){
    if(start > end)return NULL;

    Node* node = makeNode(nums[end]);

    int i;
    for(i = end;i >= start;i--){
        if(nums[i] < node->data)break;
    }

    node->left = BST(start,i);
    node->right = BST(i+1,end-1);
    

    return node;
}
void printTree(Node* root){
    printf("%d%c",root->data," \n"[++pos == numCount]);
    //printf("wee:%d\n",root->data);
    if(root->left != NULL){
        printTree(root->left);
    }
    if(root->right != NULL){
        printTree(root->right);
    }
}