#include "function.h"
#include <stdlib.h>
#include <string.h>
int check_pattern(int start, int end, char* str, char* pattern)
{
  for(int i=start; i<end; i++)
    if(str[i] != pattern[i-start])
      return 0;
  return 1;

}
void create_string(int start, int end, char* str, int* split_num, char** res)
{
  res[*split_num] = (char*)malloc((end-start+1)*sizeof(char));
  for(int i=0; i<end-start; i++)
      res[*split_num][i] = str[start+i];
  res[*split_num][end-start]='\0';
  (*split_num) ++;
}
char **split_str_by_pattern(char* str, char* pattern, int* split_num)
{
    int i=0;
    int pat_len = (int)strlen(pattern);
    int str_len = (int)strlen(str);
    char ** res = (char**)malloc(251*sizeof(char*));
    int pre_start = 0;
    *split_num = 0;

    while (i<str_len-pat_len)
    {
        int is_pat = check_pattern(i, i+pat_len, str, pattern);
        if(is_pat)
        {
            if(i-pre_start>0)
              create_string(pre_start, i, str, split_num, res);
            i+=pat_len;
            pre_start = i;
        }
        else
            i++;
    }
    if(pre_start<str_len)
        create_string(pre_start, str_len, str, split_num, res);
    return res;
}
void free_result(char **result, int split_num)
{
    for (int i=0; i<split_num; i++)
        free(result[i]);
    free(result);
}
