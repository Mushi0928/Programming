#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "codeGen.h"
#include "lex.h"

//#define debug

int sbcount = 0;
extern int cont = 1;
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

int getval(char *str,BTNode* node) {
    int i = 0;
    //exist variable
    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;
    //new variable
    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    if(node->val == __INT_MAX__)error(NOTFOUND);
    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;
}
int getAddr(char *str){
    int i = 0;
    //exist variable
    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return i*4;
    //new variable
    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return (sbcount - 1)*4;
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
    #ifdef debug
        printf("makeNode with token: %d and lexe: %s called\n",tok,lexe);
    #endif
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->rgst = -1;
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
    #ifdef debug
        printf("factor called\n");
    #endif
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {   //INT
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) { //ID
        retp = makeNode(ID, getLexeme());
        retp->val = __INT_MAX__;
        advance();
    } else if(match(INCDEC)){
        int incdec = 0;
        if(getLexeme()[0] == '+')incdec = 1;
        else incdec = -1;
        retp = makeNode(ASSIGN,"=\0");
        advance();
        if(match(ID)){
            left = makeNode(ID,getLexeme());
            retp->left = left;
                
            retp->right = makeNode(ADDSUB,"+");
            retp->right->left = makeNode(ID,getLexeme());
            retp->right->right = makeNode(INT,incdec > 0?"1":"-1");
            
            advance();
        }else{
            error(SYNTAXERR);
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
    #ifdef debug
        printf("expr with type: %d called\n",expr_type);
    #endif
    BTNode *retp,*left;
    switch(expr_type){
        case ASSIGN_EXPR:
            left = expr(OR_EXPR);
            if(match(ASSIGN)){  
                if(left->data == ID){
                    retp = makeNode(ASSIGN,getLexeme());
                    retp->left = left;
                    advance();
                    retp->right = expr(ASSIGN_EXPR);
                    return retp;
                }else{
                    err(NOTNUMID);
                }      
            }else{
                return left;
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
    #ifdef debug
        printf("expr_tail with type: %d called\n",expr_type);
        printf("left: ");
        printPrefix(left);
        printf("\n");
    #endif
    BTNode *retp = NULL,*temp = NULL;
    switch(expr_type){
        case OR_EXPR:
            if(match(OR)){
                retp = makeNode(OR,getLexeme());
                retp->left = left;
                advance();
                retp->right = expr(XOR_EXPR);
                temp = expr_tail(retp,OR_EXPR);
                if(temp != NULL)return temp; 
            }
            return retp;
            break;
        case XOR_EXPR:
            if(match(XOR)){
                retp = makeNode(XOR,getLexeme());
                retp->left = left;
                advance();
                retp->right = expr(AND_EXPR);
                temp = expr_tail(retp,XOR_EXPR);
                if(temp != NULL)return temp; 
            }
            return retp;
            break;
        case AND_EXPR:
            if(match(AND)){
                retp = makeNode(AND,getLexeme());
                retp->left = left;
                advance();
                retp->right = expr(ADDSUB_EXPR);
                temp = expr_tail(retp,AND_EXPR);
                if(temp != NULL)return temp; 
            }
            return retp;
            break;
        case ADDSUB_EXPR:
            if(match(ADDSUB)){
                retp = makeNode(ADDSUB,getLexeme());
                retp->left = left;
                advance();
                retp->right = expr(MULDIV_EXPR);
                temp = expr_tail(retp,ADDSUB_EXPR);
                if(temp != NULL)return temp; 
            }
            return retp;
            break;
        case MULDIV_EXPR:
            if(match(MULDIV)){
                retp = makeNode(MULDIV,getLexeme());
                retp->left = left;
                advance();
                retp->right = expr(UNARY_EXPR);
                temp = expr_tail(retp,MULDIV_EXPR);
                if(temp != NULL)return temp;   
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
    #ifdef debug
        printf("statement called\n");
    #endif
    BTNode *retp = NULL;
    if(match(ENDFILE)){
        cont = 0;
    }else if (match(END)) {
        //printf("\n>> ");
        advance();
    } else {
        retp = expr(ASSIGN_EXPR);
        if (match(END) || match(ENDFILE)) {
            //printf("weed\n\n\n\n\n\nweed\n");
            int ans = evaluateTree(retp);
            #ifdef debug
                printf("%d\n", ans);
                printf("Prefix traversal: ");
                printPrefix(retp);
                printf("\n");
                printf(">> ");
            #endif
            for(int i = 0;i<8;i++){
                r[i] = 0;
            }
            freeTree(retp);
            advance();
        } else {
            err(SYNTAXERR);
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
    printf("EXIT 1\n");
    exit(0);
}
