#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
char p[10];
char s[500];
char **split_str_by_pattern(char* str, char* pattern, int* split_num);
void free_result(char **result, int split_num);
int main(){

    int i, split_num;
    char **result;
    scanf("%s",s);
    scanf("%s",p);
    result = split_str_by_pattern(s, p, &split_num);
    for(i=0; i<split_num; ++i){
        printf("%s\n",result[i]);
    }
    free_result(result, split_num);
    return 0;
}
