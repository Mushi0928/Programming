#include <stdio.h>
#include <stdlib.h>

int main(){
    unsigned long long a = 1000000000;
    unsigned long long a2 = a*a;

    printf("%llu\n",a);
    printf("%llu\n",a2);
    printf("%lu",sizeof(unsigned long long));
    return 0;
}