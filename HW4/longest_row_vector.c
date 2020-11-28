#include <stdio.h>
int matrix[1000][1000];
int main(){
    int m,n,K;
    scanf("%d %d %d",&m,&n,&K);

    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            scanf("%d",&matrix[i][j]);
        }
    }
    
    for(int l = 0;l<K;l++){
        int oper,val1,val2;
        scanf("%d %d %d",&oper,&val1,&val2);
        if(oper == 0){      //swap
            for(int a = 0;a<n;a++){
                int temp = matrix[val1][a];
                matrix[val1][a] = matrix[val2][a];
                matrix[val2][a] = temp;
            }
        }else{              //add
            for(int a = 0;a<n;a++){
                matrix[val1][a] = matrix[val1][a] + matrix[val2][a];
            }
        }
    }
    
    int max = 0,max_row = 0;
    for(int a = 0;a<m;a++){
        int sum = 0;
        for(int b = 0;b<n;b++){
            sum += matrix[a][b]*matrix[a][b];
        }
        if(sum > max){
            max = sum;
            max_row = a;
        }
    }
    printf("%d",matrix[max_row][0]);
    for(int a = 1;a<n;a++){
        printf(" %d",matrix[max_row][a]);
    }
    printf("\n");
}
