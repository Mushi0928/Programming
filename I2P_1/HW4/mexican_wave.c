#include <stdio.h>

int main(){
    int T = 0;
    scanf("%d",&T);

    int counter = 0;
    while(counter < T){
        int n,m,t;
        scanf("%d %d %d",&n,&m,&t);
        
        char wave[n];
        int i = 0;
        while(i < n){
            wave[i] = '-';
            i++;
        }
        int j = 0;
        while(j<m){
            while (t+j-m < n && t+j-m >= 0){
                wave[t+j-m] = '^';
                break;    
            }
            j++;
        }
        int k = 0;
        while(k < n){
            printf("%c",wave[k]);
            k++;
        }
        printf("\n");
        counter++;
    }
    return 0;
}