#include <stdio.h>
int main(void){
    int t=0, str1_len[15]={0}, str2_len[15]={0}, flag=0, count=0;
    char a[15][1005]={0}, b[15][1005]={0};
    
    scanf("%d", &t);
    for(int i=0; i<t; i++){
        for(int j=0; j<1000; j++){
            scanf("%c", &a[i][j]);
            if(a[i][j]==32){
                a[i][j] = 0;
                str1_len[i] = j;
                break;
            }
            if(a[i][j]=='\n'&&j==0) {
                j--;
            }
        }
        for(int j=0; j<1000; j++){
            scanf("%c", &b[i][j]);
            if(b[i][j]=='\n'){
                //str2_len[i] = j-1;
                break;
            }
        }
    }
    for(int i=0; i<t; i++){
        int k=0;
        count = str1_len[i];
        for(int j=0; j<str1_len[i]; j++){
            if(a[i][j]==b[i][k]){
                if(flag == 0){
                    count = j;
                }
                flag = 1;
                k++;
            }
            else if(a[i][j]!=b[i][k] && flag==1){
                flag = 0;
                k=0;
            }
        }
        flag = 0;
        for(int j=count; j<str1_len[i]; j++){
            a[i][j]=0;
        }
    }
    for(int i=0; i<t; i++){
        for(int j=0; j<1000; j++){
            if(!a[i][j]) break;
            printf("%c", a[i][j]);
        }
        for(int j=0; j<1000; j++){
            if(!b[i][j]) break;
            printf("%c", b[i][j]);
        }
    }
    
    return 0;
}