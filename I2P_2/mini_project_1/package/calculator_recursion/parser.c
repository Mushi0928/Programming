#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "codeGen.h"
#include "lex.h"

int sbcount = 0;
Symbol table[TBLSIZE];

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str) {
    int i = 0;
    //exist variable
    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;
    //new variable
    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;
}

int setval(char *str, int val) {
    int i = 0;
    //exist variable
    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }
    //new variable
    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    printf("makeNode with token: %d and lexe: %s called\n",tok,lexe);
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// factor := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
BTNode *factor(void) {
    printf("factor called\n");
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {   //INT
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) { //ID
        retp = makeNode(ID, getLexeme());
        advance();
    } else if(match(INCDEC)){
        if(getLexeme()[0] == '+'){
            retp = makeNode(ADDSUB,"+");
        }else{
            retp = makeNode(ADDSUB,"-");
        }
        advance();
        if(match(ID)){
            left = makeNode(ID,getLexeme());
            retp->left = left;
            retp->right = makeNode(INT,"1");
            advance();
        }
    } else if (match(LPAREN)) { //LPAREN expr RPAREN
        advance();
        retp = expr(ASSIGN_EXPR);
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    } else {
        error(NOTNUMID);
    }
    return retp;
}
// expr := term expr_tail
BTNode *expr(ExprType expr_type) {
    printf("expr with type: %d called\n",expr_type);
    BTNode *retp,*left;
    switch(expr_type){
        case ASSIGN_EXPR:
            if(match(ID)){
                left = makeNode(ID,getLexeme());
                advance();
                if(match(ASSIGN)){
                    retp = makeNode(ASSIGN,getLexeme());
                    retp->left = left;
                    advance();
                    retp->right = expr(ASSIGN_EXPR);
                }else if(curToken >= OR && curToken <= MULDIV){
                    retp = expr_tail(left,curToken);
                }else if(match(END)){
                    return left;
                }
                return retp;
            }else{
                return expr(OR_EXPR);
            }
            break;
        case OR_EXPR:
            left = expr(XOR_EXPR);
            retp = expr_tail(left,OR_EXPR);
            if(retp == NULL){
                return left;
            }else{
                return retp;
            }
            break;
        case XOR_EXPR:
            left = expr(AND_EXPR);
            retp = expr_tail(left,XOR_EXPR);
            if(retp == NULL){
                return left;
            }else{
                return retp;
            }
            break;
        case AND_EXPR:
            left = expr(ADDSUB_EXPR);
            retp = expr_tail(left,AND_EXPR);
            if(retp == NULL){
                return left;
            }else{
                return retp;
            }
            break;
        case ADDSUB_EXPR:
            left = expr(MULDIV_EXPR);
            retp = expr_tail(left,ADDSUB_EXPR);
            if(retp == NULL){
                return left;
            }else{
                return retp;
            }
            break;
        case MULDIV_EXPR:
            left = expr(UNARY_EXPR);
            retp = expr_tail(left,MULDIV_EXPR);
            if(retp == NULL){
                return left;
            }else{
                return retp;
            }break;
        case UNARY_EXPR:
            if(match(ADDSUB)){
                retp = makeNode(ADDSUB,getLexeme());
                retp->left = makeNode(INT,"0");
                advance();
                retp->right = expr(UNARY_EXPR);
            }else{
                retp = factor();
            }
            return retp;
            break;
    }
}

// expr_tail := ADDSUB term expr_tail | NiL
BTNode *expr_tail(BTNode *left,ExprType expr_type) {
    printf("expr_tail with type: %d called\n",expr_type);
    printf("left: ");
    printPrefix(left);
    printf("\n");
    BTNode *retp = NULL;
    if(match(ASSIGN))err(SYNTAXERR);
    switch(expr_type){
        case OR_EXPR:
            if(match(OR)){
                retp = makeNode(OR,getLexeme());
                retp->left = left;
                advance();
                retp->right = expr(OR_EXPR);
            }
            return retp;
            break;
        case XOR_EXPR:
            if(match(XOR)){
                retp = makeNode(XOR,getLexeme());
                retp->left = left;
                advance();
                retp->right = expr(XOR_EXPR);
            }
            return retp;
            break;
        case AND_EXPR:
            if(match(AND)){
                retp = makeNode(AND,getLexeme());
                retp->left = left;
                advance();
                retp->right = expr(AND_EXPR);
            }
            return retp;
            break;
        case ADDSUB_EXPR:
            if(match(ADDSUB)){
                retp = makeNode(ADDSUB,getLexeme());
                retp->left = left;
                advance();
                retp->right = expr(ADDSUB_EXPR);
            }
            return retp;
            break;
        case MULDIV_EXPR:
            if(match(MULDIV)){
                retp = makeNode(MULDIV,getLexeme());
                retp->left = left;
                advance();
                retp->right = expr(MULDIV_EXPR);
            }
            return retp;
            break;
        default:
            return NULL;
            break;
    }
}

// statement := END | assign_expr END 
void statement(void) {
    printf("statement called\n");
    BTNode *retp = NULL;

    if (match(END)) {
        printf("\n>> ");
        advance();
    } else {
        retp = expr(ASSIGN_EXPR);
        if (match(END)) {
            //printf("%d\n", evaluateTree(retp));
            printf("Prefix traversal: ");
            printPrefix(retp);
            printf("\n");
            freeTree(retp);
            printf(">> ");
            advance();
        } else {
            //err(SYNTAXERR);
        }
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    exit(0);
}
