#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeGen.h"
#include "parser.h"


extern int r[regSize] = { 0 };
int memoryPos = 0;
int getValidRgst(){
    for(int i = 0;i<regSize;i++){
        if(r[i] == 0){
            r[i] = 1;
            return i;
        }
    }
    printf("MOV [%d] r%d\n",(TBLSIZE - 1 - memoryPos)*4,memoryPos%regSize);
    table[TBLSIZE - 1 - memoryPos].val = memoryPos%regSize;
    return memoryPos++;
}
void freeRgst(BTNode* node){
    //printf("%d\n",node->rgst);
    if(node->rgst < memoryPos){
        memoryPos--;
        printf("MOV r%d [%d]\n",memoryPos%regSize,(TBLSIZE - 1 - memoryPos)*4);
    }else{
        r[node->rgst] = 0;
    }
    node->rgst = -1;
    
    
}
int onlyINT(BTNode* root){
    if(root == NULL)return 1;
    if(root->data == ID){
        return 0;
    }else if(!onlyINT(root->left) || !onlyINT(root->right)){
        return 0;
    }else{
        return 1;
    }
}
int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0,data,addr,rgst;

    if (root != NULL) {
        #ifdef debug
            printf("evaluateTree called with token: %d\n",root->data);
        #endif
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme,root);
                addr = getAddr(root->lexeme);
                rgst = getValidRgst();
                root->rgst = rgst;
                printf("MOV r%d [%d]\n",rgst,addr);
                break;
            case INT:
                retval = atoi(root->lexeme);
                rgst = getValidRgst();
                root->rgst = rgst;
                printf("MOV r%d %d\n",rgst,retval);
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                root->left->val = 0;
                int addr = getAddr(root->left->lexeme);
                rgst = root->right->rgst;
                printf("MOV [%d] r%d\n",addr,rgst);
                root->rgst = root->right->rgst;
                
                
                break;
            case ADDSUB:
                data = root->right->data;
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                    printf("ADD r%d r%d\n",root->left->rgst,root->right->rgst);
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                    printf("SUB r%d r%d\n",root->left->rgst,root->right->rgst);  
                }
                freeRgst(root->right);
                root->rgst = root->left->rgst;
                root->left->rgst = -1;
                break;
            case MULDIV:
                data = root->right->data;
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                    printf("MUL r%d r%d\n",root->left->rgst,root->right->rgst);
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0){
                        if(onlyINT(root->right)){
                            error(DIVZERO);
                        }else{
                            retval = 0;
                        }
                    }else{
                        retval = lv / rv;
                    }
                    printf("DIV r%d r%d\n",root->left->rgst,root->right->rgst);
                }
                freeRgst(root->right);
                root->rgst = root->left->rgst;
                root->left->rgst = -1;
                break;
            case INCDEC://shouldn't be called
                lv = evaluateTree(root->left);
                addr = getAddr(root->left->lexeme);
                rgst = getValidRgst();
                printf("MOV r%d 1\n",rgst);
                if (strcmp(root->lexeme, "++") == 0){
                    retval = setval(root->left->lexeme,lv+1);
                    printf("ADD r%d r%d\n",root->left->rgst,rgst);
                }else if(strcmp(root->lexeme, "--") == 0){
                    retval = setval(root->left->lexeme,lv-1);
                    printf("SUB r%d r%d\n",root->left->rgst,rgst);
                }
                printf("MOV [%d] r%d\n",addr,root->left->rgst);
                r[root->left->rgst] = 0;
                r[rgst] = 0;
                root->rgst = root->left->rgst;
                //freeRgst(root->left);
                break;
            case OR:
                data = root->right->data;
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                retval = lv | rv;
                printf("OR r%d r%d\n",root->left->rgst,root->right->rgst);
                freeRgst(root->right);
                root->rgst = root->left->rgst;
                root->left->rgst = -1;
                break;
            case XOR:
                data = root->right->data;
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                retval = lv ^ rv;
                printf("XOR r%d r%d\n",root->left->rgst,root->right->rgst);
                freeRgst(root->right);
                root->rgst = root->left->rgst;
                root->left->rgst = -1;
                break;
            case AND:
                data = root->right->data;
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                retval = lv & rv;
                printf("AND r%d r%d\n",root->left->rgst,root->right->rgst);
                freeRgst(root->right);
                root->rgst = root->left->rgst;
                root->left->rgst = -1;
                break;
            default:
                retval = 0;
                break;
        }
    }
    return retval;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
