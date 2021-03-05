#include <stdio.h>
#include <ctype.h>
float prefix(){

    float num1,num2,ans;
    char temp;
    while(isspace(temp = getchar()));
    if(temp == '+'){
        printf("( ");
        num1 = prefix();
        printf(" + ");
        num2 = prefix();
        printf(" )");
        ans = num1 + num2;
    }else if(temp == '-'){
        printf("( ");
        num1 = prefix();
        printf(" - ");
        num2 = prefix();
        printf(" )");
        ans = num1 - num2;
    }else if(temp == '*'){
        printf("( ");
        num1 = prefix();
        printf(" * ");
        num2 = prefix();
        printf(" )");
        ans = num1 * num2;
    }else if(temp == '/'){
        printf("( ");
        num1 = prefix();
        printf(" / ");
        num2 = prefix();
        printf(" )");
        ans = num1 / num2;
    }else{
        int get;
        ungetc(temp,stdin);
        scanf("%d",&get);
        printf("%d",get);
        ans = (float)get;
    }
    return ans;
}
int main(){
    int T;
    int left = 0;
    scanf("%d",&T);
    for(int i = 0;i<T;i++){
        float temp = prefix();
        if( (temp - (int)temp) == 0){
            printf(" = %d\n",(int)temp);
        }else{
            printf(" = %.1f\n",temp);
        }
    }
    return 0;
}