#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"
#include "codeGen.h"
#include "parser.h"

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
    freopen("assembly.txt", "w", stdout);
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
