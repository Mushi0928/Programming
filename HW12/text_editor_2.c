#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct word{
    char alpha;
    struct word* last;
    struct word* next;
}Word;
char input[6000];

Word* cursor = NULL;
Word* head = NULL;
int main(){
    fgets(input, 1000, stdin);
    for(int i = 0;i<strlen(input);i++){
        //printf("%c ",input[i]);
        if(input[i] == '/'){
            //printf("%c\n",input[i+1]);
            switch(input[i+1]){
                case 'b':
                    i += 9;
                    if(cursor == NULL)
                        break;
                    if(cursor->last != NULL){
                        if(cursor->next != NULL){ //both not null
                            Word* temp = cursor;
                            (cursor->last)->next = cursor->next;
                            (cursor->next)->last = cursor->last;
                            cursor = cursor->last;
                            free(temp);
                        }else{  //only last
                            cursor = cursor->last;
                            free(cursor->next);
                            cursor->next = NULL;
                        }
                    }else if(cursor->next != NULL){ //only next
                        cursor = cursor->next;
                        free(cursor->last);
                        cursor->last = NULL;
                        head = cursor;
                        
                    }else{  //both null
                        free(cursor);
                        cursor = NULL;
                        head = cursor;
                    }
                    break;
                case 'n':
                    input[i+7] = '\n';
                    i += 6;
                    break;
                case 'l':
                    if(cursor != NULL && cursor->last != NULL){
                        cursor = cursor->last;
                    }
                    i += 4;
                    break;
                case 'r':
                    if(cursor != NULL && cursor->next != NULL){
                        cursor = cursor->next;
                    }
                    i += 5;
                    break;
            }
        }else{
            Word* temp = (Word*)malloc(sizeof(Word));
            temp->alpha = input[i];
            temp->last = NULL;
            temp->next = NULL;
            if(cursor != NULL){
                if(cursor->next != NULL){
                    (cursor->next)->last = temp;
                    temp->next = cursor->next;
                    cursor->next = temp;
                    temp->last = cursor;
                }else{
                    temp->last = cursor;
                    cursor->next = temp;
                }
                cursor = temp;
            }else{
                cursor = temp;
                head = cursor;
            }
        }
    }
    /*
    printf("B\n");
    while(cursor->last != NULL){
        printf("%c ",cursor->alpha);
        //printf("GG\n");
        if(cursor == cursor->last){
            printf("dafuq\n");
            break;
        }
        cursor = cursor->last;
    }
    */
    //printf("C\n");

    while(head->next != NULL){
        //printf("%p ",head->next);
        printf("%c",head->alpha);
        //printf("GG2\n");
        Word* temp = head->next;
        //printf(" %p\n",temp->next);
        if(head->next == temp->next){
            break;
        }
        head = temp;
    }
    printf("%c",head->alpha);

    return 0;
}