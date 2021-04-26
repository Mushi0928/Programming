#ifndef __LEX__
#define __LEX__

#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE, 
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN, 
    LPAREN, RPAREN,
    INCDEC, INCDEC_A,       //新加的define
    AND, OR, XOR
} TokenSet;

// Test if a token matches the current token 
extern int match(TokenSet token);

// Get the next token
extern void advance(void);

// Get the lexeme of the current token
extern char *getLexeme(void);

#endif // __LEX__
#ifndef __PARSER__
#define __PARSER__


#define TBLSIZE 64

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 1

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        printf("EXIT 1\n");\
        exit(0);\
}
/*
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \     //暫時拿掉
        err(errorNum); \
*/

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left; 
    struct _Node *right;
} BTNode;

// The symbol table
extern Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
extern void initTable(void);

// Get the value of a variable
extern int getval(char *str);

// Set the value of a variable
extern int setval(char *str, int val);

// Make a new node according to token type and lexeme
extern BTNode *makeNode(TokenSet tok, const char *lexe);

// Free the syntax tree
extern void freeTree(BTNode *root);

extern BTNode *factor(void);
extern BTNode *term(void);
extern BTNode *term_tail(BTNode *left);
extern BTNode *expr(void);
extern BTNode *assign_expr(void);
extern BTNode *or_expr(void);
extern BTNode *xor_expr(void);
extern BTNode *and_expr(void);
extern BTNode *addsub_expr(void);
extern BTNode *muldiv_expr(void);
extern BTNode *unary_expr(void);
extern BTNode *expr_tail(BTNode *left);
extern BTNode *or_expr_tail(BTNode *left);
extern BTNode *xor_expr_tail(BTNode *left);
extern BTNode *and_expr_tail(BTNode *left);
extern BTNode *addsub_expr_tail(BTNode *left);
extern BTNode *muldiv_expr_tail(BTNode *left);
extern void statement(void);

// Print error message and exit the program
extern void err(ErrorType errorNum);

#endif // __PARSER__
#ifndef __CODEGEN__
#define __CODEGEN__



// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);
int evaluateTree_M(BTNode root, int sbcount);
void clear_r(void);
int check_div_zero(BTNode *root);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);

#endif // __CODEGEN__
#include <stdio.h>
#include <string.h>
#include <ctype.h>


static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        c = fgetc(stdin);
        if(c==lexeme[0] || c==lexeme[0]) {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }
        else{
            ungetc(c, stdin);
            lexeme[1] = '\0';
            return ADDSUB;
        }
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c=='_') {     //變數名字可以是很多字母, 非開頭可以是數字, 名字長度可以有256個
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isalpha(c) || isdigit(c) || c=='_') && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        // if(c) 不合法
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == '&') {      //新加的&運算
        lexeme[0] = c;
        lexeme[1] = '\0';
        return AND;
    } else if (c == '|') {      //新加的|運算
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OR;
    } else if (c == '^') {      //新加的^運算
        lexeme[0] = c;
        lexeme[1] = '\0';
        return XOR;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    /*if (sbcount >= TBLSIZE)*/
        error(RUNOUT);
    
    /*strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;*/
    return 0;
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    //printf("%d\n", sbcount);
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    if(node->data==INCDEC){
        node->data = ADDSUB;
        strcpy(node->lexeme, lexe+1);
    }
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

// factor := INT | ADDSUB INT |
//       ID  | ADDSUB ID  | 
//       ID ASSIGN expr |
//       LPAREN expr RPAREN |
//       ADDSUB LPAREN expr RPAREN
BTNode *factor(void) {                   //目前要改最主要的地方
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
        advance();
        /*left = makeNode(ID, getLexeme());
        advance();
        if (!match(ASSIGN)) {
            retp = left;
        } else {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = or_expr();
        }*/
    } else if (match(INCDEC)) {     //改
        left = makeNode(INCDEC, getLexeme());
        //printf("%s %s\n", getLexeme(), left->lexeme);
        advance();
        if (!match(ID)) {
            //printf("NOT\n");
            error(NOTNUMID);
        } else {
            retp = makeNode(INCDEC_A, "=");
            retp->left = makeNode(ID, getLexeme());
            //printf("%s\n", getLexeme());
            if((retp->left)->data==ID){
                retp->right = left;
                (retp->right)->left = makeNode(ID, getLexeme());
                //printf("%s\n", getLexeme());
                (retp->right)->right = makeNode(INT, "1");
                advance();
                //printf("%s\n", getLexeme());
            } else error(NOTNUMID);
        }
    } /*else if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        retp->left = makeNode(INT, "0"); //???
        advance();
        if (match(INT)) {
            retp->right = makeNode(INT, getLexeme());
            advance();
        } else if (match(ID)) {
            retp->right = makeNode(ID, getLexeme());
            advance();
        } else if (match(ASSIGN)) {
            error(NOTNUMID);
        } else if (match(LPAREN)) {
            advance();
            retp->right = assign_expr();
            if (match(RPAREN))
                advance();
            else
                error(MISPAREN);
        } else {
            error(NOTNUMID);
        }
    }*/ else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    } else {
        error(NOTNUMID);
    }
    return retp;
}

// term := factor term_tail
BTNode *term(void) {
    BTNode *node = factor();
    return term_tail(node);
}

// term_tail := MULDIV factor term_tail | NiL
BTNode *term_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = factor();
        if((node->right)->data==ASSIGN){
            error(NOTNUMID);
        }
        ret