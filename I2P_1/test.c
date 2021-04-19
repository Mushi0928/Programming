/*
#include<stdio.h>

int main(){
    printf(" ^   ^      \n");
    printf("(=-w-=)----?\n");
    printf("  \" \"   \" \" \n");
    return 0;
}
*/

/*
#include<stdio.h>

int main(){
    int a,b,c,num;
    scanf("%d",&num);
    c = num % 10;
    b = (num / 10) % 10;
    a = (num / 100);

    printf("%.1f",(num + c*100 + b*10 + a)/2.0);
    return 0;
}
*/
/*
#include<stdio.h>
#include<string.h>
int main(){
    char T[4];
    int t[4];
    scanf("%s",T);

    t[0] = T[0] - 48;
    t[1] = T[1] - 48;
    t[2] = T[2] - 48;
    t[3] = T[3] - 48;
    
    int H = t[0]*10 + t[1];
    int M = t[2]*10 + t[3];

    int flag = H/12;
    H = H - 12*flag;

    int AP = 'p'*(flag%2) + 'a'*((flag+1)%2);
    printf("%d%d:%d%d %c.m.",H/10,H%10,t[2],t[3],AP);
    return 0;
}
*/
/*
#include<stdio.h>

int main(){
    char word[5];
    scanf("%s",word);

    printf("%c%c%c%c%c\n",122 - (word[0] - 97),122 - (word[1] - 97),122 - (word[2] - 97),122 - (word[3] - 97),122 - (word[4] - 97));
    return 0;
}
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int dick = 2;
int a[2][2] = {{1,2},{3,4}};
void read(int b[dick][dick]){
    printf("%d",b[1][1]);
}
int main(){
    read(a);
    return 0;
}