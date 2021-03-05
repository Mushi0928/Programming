#include <stdio.h>
#include <string.h>

int n,m;
char string[200001];
char trans[26];

int main(){
    scanf("%d %d",&n,&m);
    scanf("%s\n",string);
    for(int i = 0;i<26;i++){
        trans[i] = 'a' + i; 
    }
    for(int i = 0;i<m;i++){
        char x,y;
        scanf("%c %c\n",&x,&y);
        //printf("%c %c\n",x,y);
        for(int j = 0;j<26;j++){
            if(trans[j] == x)trans[j] = y;
            else if(trans[j] == y)trans[j] = x;
        }
    }
    for(int i = 0;i<n;i++){
        string[i] = trans[string[i]-'a'];
    }
    //printf("%s\n",trans);
    printf("%s\n",string);
    return 0;
}