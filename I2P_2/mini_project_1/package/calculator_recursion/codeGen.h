#ifndef __CODEGEN__
#define __CODEGEN__
#define regSize 8
#include "parser.h"
extern int pos;
extern int r[regSize];
// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);

#endif // __CODEGEN__
