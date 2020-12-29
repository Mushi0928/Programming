#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char s[2000] = {0};
char ans[550] = {0};
int flag = 0, flagb = 0, flaglr = 0;
int main(void){
    fgets(s, 2000, stdin);
    int len = strlen(s);
    int pos = 0;
    for(int i=0; i<len-1; i++){
        if(s[i]=='/'){
            flag = 1;
            continue;
        }
        if(flag){
            if(s[i]=='b'){
                pos--;
                if(pos<0) pos = 0;
                for(int j=pos; j<strlen(ans); j++){
                    ans[j] = ans[j+1];
                }
                i = i+8;
                flagb++;
            }
            else if(s[i]=='n'){
                if(!flagb){
                    for(int j=strlen(ans); j>pos; j--){
                        ans[j] = ans[j-1];
                    }
                }
                ans[pos++] = '\n';
                i = i+6;
            }
            else if(s[i]=='l'){
                pos--;
                if(pos<0) pos = 0;
                i = i+3;
                flaglr++;
            }
            else if(s[i]=='r'){
                int lenans = strlen(ans);
                pos++;
                if(pos>lenans) pos = lenans;
                i = i+4;
                flaglr++;
            }
            flag = 0;
        }
        else {
            if(!flagb || (flagb && flaglr)){
                for(int j=strlen(ans); j>pos; j--){
                    ans[j] = ans[j-1];
                }
            }
            ans[pos++] = s[i];
            if(flaglr>0) flaglr--;
            if(flagb>0) flagb--;
        }
    }
    /*fgets(s, 500, stdin);
    fputs(s, stdout);*/
    printf("%s", ans);
    return 0;
}