#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct _line{
    int number;
    char* content;
    int max_len;
    int len;
    Line* next;
    Line* last;
}Line;

int T;
bool mode;//true -> command ,false -> insert
int cursorX = 0;

int n = 0;
char n_move_type;
bool have_n = false;
char n_move_str[2000] = {'\0'};
int n_move_str_cursor = 0;

char input[2005];
Line* head;
int main(){
    scanf("%d",&T);
    for(int i = 0;i<T;i++){
        head = (Line*)malloc(sizeof(Line));
        head->content = (char*)malloc(100*sizeof(char));
        head->content[0] = '\0';
        head->number = 1;
        head->next = NULL;
        head->last = NULL;
        head->len = 0;
        head->max_len = 100;
        scanf("%s",input);
        for(int j = 0;j<strlen(input);j++){
            if(input[j] == ':' && input[j+1] == 'w' && input[j+2] == 'q')break;
            if(mode){//command mode
                switch(input[j]){
                    case 'h':
                        if(!have_n){
                            if(cursorX > 0)cursorX--;
                        }else{
                            if(cursorX > n)cursorX -= n;
                            else cursorX = 0;
                            n = 0;
                            have_n = false;
                        }
                        break;
                    case 'l':
                        if(!have_n){
                            if(cursorX < head->len)cursorX++; 
                        }else{
                            if(cursorX + n <= head->len)cursorX += n;
                            else cursorX = head->len;
                            n = 0;
                            have_n = false;
                        }
                        break;
                    case 'x':
                        if(cursorX != 0){
                            for(int k = cursorX;k<head->len;k++){
                                head->content[k-1] = head->content[k];
                            }
                            head->len--;
                            head->content[head->len] = '\0';
                        }
                        break;
                    case 'j':
                        if(!have_n){
                            if(head->next == NULL && head->number <= 1000 && (head->next)->number == (head->number+1)){
                                head->next = (Line*)malloc(sizeof(Line));
                                (head->next)->content = (char*)malloc(100*sizeof(char));
                                (head->next)->content[0] = '\0';
                                (head->next)->number = head->number+1;
                                (head->next)->next = NULL;
                                (head->next)->last = head;
                                (head->next)->len = 0;
                                (head->next)->max_len = 100;
                                head = head->next;
                                cursorX = 0;
                            }else if((head->next)->len < head->len){
                                head = head->next;
                                cursorX = head->len;
                            }else{
                                head = head->next;
                            }
                        }else{
                            for(int l = 0;l < n;l++){
                                if(head->next == NULL && head->number <= 1000 && (head->next)->number == (head->number+1)){
                                head->next = (Line*)malloc(sizeof(Line));
                                (head->next)->content = (char*)malloc(100*sizeof(char));
                                (head->next)->content[0] = '\0';
                                (head->next)->number = head->number+1;
                                (head->next)->next = NULL;
                                (head->next)->last = head;
                                (head->next)->len = 0;
                                (head->next)->max_len = 100;
                                head = head->next;
                                cursorX = 0;
                                }else if((head->next)->len < head->len){
                                    head = head->next;
                                    cursorX = head->len;
                                }else{
                                    head = head->next;
                                }
                            }
                            n = 0;
                            have_n = false;
                        break;
                    case 'k':
                        if(!have_n){
                            if(head->number > 1){
                                if((head->last)->len < head->len){
                                    cursorX = (head->last)->len;
                                }
                                head = head->last;
                            }
                        }else{
                            for(int l = 0;l < n;l++){
                                if(head->number > 1){
                                    if((head->last)->len < head->len){
                                        cursorX = (head->last)->len;
                                    }
                                    head = head->last;
                                }
                            }
                        }
                        break;
                    case 'a':
                        if(have_n)n_move_type = 'a';
                        mode = false;
                        break;
                    case 'A':
                        if(have_n)n_move_type = 'A';
                        cursorX = head->len;
                        mode = false;
                        break;
                    case 'i':
                        if(have_n)n_move_type = 'i';
                        if(cursorX != 0)cursorX--;
                        mode = false;
                        break;
                    case 'I':
                        if(have_n)n_move_type = 'I';
                        cursorX = 0;
                        mode = false;
                        break;
                    case '0' ... '9':
                        n = n*10 + input[j] - '0';
                        have_n = true;
                        break;

                }
            }else{//insert mode
                if(input[j] = 'E' && input[j+1] == 'S' && input[j+2] == 'C'){
                    if(have_n){

                    }else{
                        if(cursorX == 0 && head->len != 0)cursorX = 1;
                        mode = true;
                    }
                }
                if(have_n){
                    n_move_str[n_move_str_cursor] = input[j];
                    n_move_str_cursor++;
                }else{
                    if(head->len < head->max_len - 1){
                        head->content[head->len] = input[j];
                        head->len++;
                        head->content[head->len] = '\0';
                    }else{
                        head->max_len += 100;
                        char* temp = (char*)malloc((head->max_len)*sizeof(char));
                        free(head->content);
                        head->content = temp;
                        head->content[head->len] = input[j];
                        head->len++;
                        head->content[head->len] = '\0';
                    }
                }
            }
        }
    }
}