#include "function.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
char **split_str_by_pattern(char* str, char* pattern, int* split_num){
    int str_len = strlen(str);
    int patt_len = strlen(pattern);
    int patt_pos[505] = { 0 };
    int total = 0;
    (*split_num) = 0;

    for(int i = 0;i<str_len-patt_len+1;i++){
        int valid = 1;
        for(int j = 0;j<patt_len;j++){
            if(str[i+j] != pattern[j]){
                valid = 0;
                break;
            }
        }
        if(valid){
            patt_pos[total] = i;
            //printf("%d\n",patt_pos[flag]);
            total++;
            i += (patt_len - 1);
        }
    }

    char** rows = malloc(sizeof(char*)*(total+1));
    char* strings = malloc(sizeof(char)*(total+1)*505);
    for(int i = 0;i<total+1;i++){
        rows[i] = strings + (505*i);
    }
    int leftCursor = 0,rightCursor = 0;
    int resultCursor = 0;
    for(int i = 0;i<total;i++){
        rightCursor = patt_pos[i];
        if(leftCursor == rightCursor){

        }else{
            for(int j = leftCursor;j<rightCursor;j++){
                rows[(*split_num)][j-leftCursor] = str[j];
            }
            rows[(*split_num)][rightCursor-leftCursor] = '\0';
            (*split_num)++;
        }
        leftCursor = rightCursor+patt_len;
    }
    if(leftCursor == str_len){
        //rows[(*split_num)][0] = '\0';
    }else{
        for(int j = leftCursor;j<str_len;j++){
            rows[(*split_num)][j-leftCursor] = str[j];            
        }
        rows[(*split_num)][str_len-leftCursor] = '\0';
        (*split_num)++;
    }
    
    
    return rows;
}
void free_result(char **result, int split_num){
    free(result[0]);
    free(result);
}