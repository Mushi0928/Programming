#include <stdio.h>

void OUQ(int layer);

int k,l,r;
int flag = 0;
int main(){
    while(scanf("%d %d %d",&k,&l,&r) > 1){
        OUQ(k);
        printf("\n");
        flag = 0;
    }
}
void OUQ(int layer){
    //printf("%d",layer);
    if(flag > r)return;
    //O
    if(flag >= l)printf("O");
    flag++;
    if(flag > r)return;
    //S(k-1)
    if(layer > 1)OUQ(layer-1);
    if(flag > r)return;
    //u
    if(flag >= l)printf("u");
    flag++;
    if(flag > r)return;
    //S(k-1)
    if(layer > 1)OUQ(layer-1);
    if(flag > r)return;
    //Q
    if(flag >= l)printf("Q");
    flag++;
    if(flag > r)return;
}