#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"
#include "parser.h"

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
