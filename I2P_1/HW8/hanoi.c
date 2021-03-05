#include <stdio.h>
void hanoi(char from,char buffer,char to,int layer){
    if(layer == 1){
        printf("1\n");
    }else{
        hanoi(from,to,buffer,layer-1);

        printf("%d\n",layer);

        hanoi(buffer,from,to,layer-1);
    }
}
int main(){
    int n;
    scanf("%d", &n);
    hanoi('A', 'B', 'C',n);
    return 0;
}