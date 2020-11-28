#include <stdio.h>
#include <ctype.h>

int compare(char a[],char b[]);
int main(){
    int T;

    scanf("%d",&T);
    for(int i = 0;i<T;i++){
        int cards[13],compose[6];
        for(int j = 0;j<13;j++)cards[j] = 0;
        for(int j = 0;j<5;j++){
            char temp[10];
            scanf("%s",temp);
            if(compare(temp,"A")){
                cards[0]++;
            }else if(compare(temp,"2")){
                cards[1]++;
            }else if(compare(temp,"3")){
                cards[2]++;
            }else if(compare(temp,"4")){
                cards[3]++;
            }else if(compare(temp,"5")){
                cards[4]++;
            }else if(compare(temp,"6")){
                cards[5]++;
            }else if(compare(temp,"7")){
                cards[6]++;
            }else if(compare(temp,"8")){
                cards[7]++;
            }else if(compare(temp,"9")){
                cards[8]++;
            }else if(compare(temp,"10")){
                cards[9]++;
            }else if(compare(temp,"J")){
                cards[10]++;
            }else if(compare(temp,"Q")){
                cards[11]++;
            }else if(compare(temp,"K")){
                cards[12]++;
            }
        }
        for(int j = 0;j<5;j++){
            compose[j] = 0;
        }
        for(int j = 0;j<13;j++){
            compose[cards[j]]++;
        }
        for(int j = 0;j<5;j++){
            //printf("%d",compose[j]);
        }
        if(compose[2] == 1 && compose[3] == 1){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }

    return 0;
}
int compare(char a[],char b[]){
    if(a[0] == b[0] && a[1] == b[1]){
        return 1;
    }else{
        return 0;
    }
}