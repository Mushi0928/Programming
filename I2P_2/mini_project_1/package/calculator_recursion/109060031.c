#ifndef __LEX__
#define __LEX__

#define MAXLEN 256

// Token types
typedef enum { 
    UNKNOWN,
    OR, XOR, AND,
    ADDSUB, MULDIV,   
    END,    //\n 
    ENDFILE, 
    INT, ID,
    INCDEC,
    ASSIGN, 
    LPAREN, RPAREN
} TokenSet;


// Test if a token matches the current token 
extern int match(TokenSet token);
extern TokenSet curToken;
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
#define PRINTERR 0

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED,
    MISPAREN, //parentheses got something wrong
    NOTNUMID, 
    NOTFOUND, 
    RUNOUT, //too many variables
    NOTLVAL, 
    DIVZERO, 
    SYNTAXERR
} ErrorType;

typedef enum {
    ASSIGN_EXPR,
    OR_EXPR,
    XOR_EXPR,
    AND_EXPR,
    ADDSUB_EXPR,
    MULDIV_EXPR,
    UNARY_EXPR,
}ExprType;

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
    int rgst;
    struct _Node *left; 
    struct _Node *right;
} BTNode;

// The symbol table
extern Symbol table[TBLSIZE];

extern int cont;
// Initialize the symbol table with builtin variables
extern void initTable(void);

// Get the value of a variable
extern int getval(char *str,BTNode* node);
// Get the memory address of a variable
extern int getAddr(char *str);
// Set the value of a variable
extern int setval(char *str, int val);

// Make a new node according to token type and lexeme
extern BTNode *makeNode(TokenSet tok, const char *lexe);

// Free the syntax tree
extern void freeTree(BTNode *root);

extern BTNode *factor(void);
extern BTNode *term(void);
extern BTNode *term_tail(BTNode *left);
extern BTNode *expr(ExprType);
extern BTNode *expr_tail(BTNode *left,ExprType);
extern void statement(void);

// Print error message and exit the program
extern void err(ErrorType errorNum);

#endif // __PARSER__
#ifndef __CODEGEN__
#define __CODEGEN__
#define regSize 8

extern int pos;
extern int r[regSize];
// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);

#endif // __CODEGEN__
#include <stdio.h>
#include <string.h>
#include <ctype.h>



static TokenSet getToken(void);
extern TokenSet curToken = UNKNOWN;
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
        while (1) {
            if(isdigit(c) && i < MAXLEN){
                lexeme[i] = c;
                ++i;
                c = fgetc(stdin);
            }else if(isalpha(c) || c == '_'){  //variable starts with number
                err(SYNTAXERR);
                break;
            }else{
                break;
            }
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        char temp = fgetc(stdin);
        if(temp == c){
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }else{
            lexeme[1] = '\0';
            ungetc(temp,stdin);
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
    } else if(c == '&'){
        strcpy(lexeme, "&");
        return AND;
    } else if(c == '|'){
        strcpy(lexeme, "|");
        return OR;
    } else if(c == '^'){
        strcpy(lexeme, "^");
        return XOR;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (1) {
            if((isalpha(c) || isdigit(c) || c == '_') && (i < MAXLEN)){
                lexeme[i] = c;
                ++i;
                c = fgetc(stdin);
            } else{
                ungetc(c, stdin);
                break;
            }
        }
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
    #ifdef debug
        printf("advanced with Token: %d\n",curToken);
    #endif
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>




// This package is a calculator
// It works like a Python interpretor
// Example:
// >> y = 2
// >> z = 2
// >> x = 3 * y + 4 / (2 * z)
// It will print the answer of every line
// You should turn it into an expression compiler
// And print the assembly code according to the input

// This is the grammar used in this package
// You can modify it according to the spec and the slide
// statement  :=  ENDFILE | END | expr END
// expr    	  :=  term expr_tail
// expr_tail  :=  ADDSUB term expr_tail | NiL
// term 	  :=  factor term_tail
// term_tail  :=  MULDIV factor term_tail| NiL
// factor	  :=  INT | ADDSUB INT |
//		   	      ID  | ADDSUB ID  | 
//		   	      ID ASSIGN expr |
//		   	      LPAREN expr RPAREN |
//		   	      ADDSUB LPAREN expr RPAREN

int main() {
    cont = 1;
    //freopen("assembly.txt", "w", stdout);
    initTable();
    //printf(">> ");
    while (cont) {
        statement();
    }
    printf("MOV r0 [0]\n"
            "MOV r1 [4]\n"
            "MOV r2 [8]\n");
    printf("EXIT 0\n");
    return 0;
}
