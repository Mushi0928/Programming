#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeGen.h"
#include "parser.h"

int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme);
                int addr = getAddr(root->lexeme);
                printf("MOV r3, [%d]\n",addr);
                break;
            case INT:
                retval = atoi(root->lexeme);
                printf("MOV r3, %d\n",retval);
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                int lAddr = getAddr(root->left->lexeme);
                printf("MOV [%d], r3\n",lAddr);
                break;
            case ADDSUB:
                lv = evaluateTree(root->left);
                printf("MOV r4, r3\n");
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                    printf("ADD r3, r4\n");
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                    printf("ADD r4, r3\n");
                    printf("MOV r3, r4\n");
                }
            case MULDIV:
                lv = evaluateTree(root->left);
                printf("MOV r4, r3\n");
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                    printf("MUL r3, r4\n");
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0)
                        error(DIVZERO);
                    retval = lv / rv;
                    printf("DIV r4, r3\n");
                    printf("MOV r3, r4\n");
                }
                break;
            case INCDEC:
                lv = evaluateTree(root->left);
                getAddr(root->left->lexeme);
                printf("MOV r5, 1\n");
                if (strcmp(root->lexeme, "++") == 0){
                    retval = setval(root->left->lexeme,lv+1);
                    printf("ADD r3, r5\n");
                }else if(strcmp(root->lexeme, "--") == 0){
                    retval = setval(root->left->lexeme,lv-1);
                    printf("SUB r3, r5\n");
                }
                printf("MOV [%d], r3\n",addr);
                break;
            case OR:
                lv = evaluateTree(root->left);
                printf("MOV r4, r3\n");
                rv = evaluateTree(root->right);
                retval = lv | rv;
                printf("OR r3, r4\n");
                break;
            case XOR:
                lv = evaluateTree(root->left);
                printf("MOV r4, r3\n");
                rv = evaluateTree(root->right);
                retval = lv ^ rv;
                printf("XOR r3, r4\n");
                break;
            case AND:
                lv = evaluateTree(root->left);
                printf("MOV r4, r3\n");
                rv = evaluateTree(root->right);
                retval = lv & rv;
                printf("AND r3, r4\n");
                break;
            default:
                retval = 0;
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
