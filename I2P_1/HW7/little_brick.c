#include <stdio.h>
int gcd(int a,int b);
int lcm(int a,int b);
int power(int a,int b);

int main(){
    
    int a,b,c,d;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    printf("%d\n",gcd(lcm(power(a,b),c),d));
    printf("%d\n",gcd(power(lcm(a,b),c),d));
    printf("%d\n",lcm(gcd(power(a,b),c),d));
    printf("%d\n",lcm(power(gcd(a,b),c),d));
    printf("%d\n",power(gcd(lcm(a,b),c),d));
    printf("%d\n",power(lcm(gcd(a,b),c),d));
    
    return 0;
}
int gcd(int a,int b){
    if(a == 0||b == 0)return (a+b);
    if(a%b == 0){
        return (a>b)?b:a;
    }else{
        if(a>b)return gcd(a%b,b);
        else return gcd(a,b%a);
    } 
}
int lcm(int a,int b){
    return a*b/gcd(a,b);
}
int power(int a,int b){
    if(b > 0)return a*power(a,b-1);
    else return 1;
}