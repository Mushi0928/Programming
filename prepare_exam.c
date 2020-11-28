#include <stdio.h>

int main(){
    int N;      //應該不用解釋這個吧
    scanf("%d",&N);

    int practices[2][N];        //一個存多少題跟練多少題的陣列
    for(int i = 0;i<2;i++){         //就...scanf
        for(int j = 0;j<N;j++){
            scanf("%d",&practices[i][j]);
        }
    }
    

    int C[101][101];        //存x和y在範圍內時所有Ｃ的值
    for(int i = 0;i<101;i++){   //Ｃn取1 和 Ｃn取n 不能用題目給的公式求 所以自己設
        C[i][1] = i;
        C[i][i] = 1;
    }
    for(int n = 2;n<101;n++){       //就帶入題目上的公式 一個一個把所有的Ｃ求出來 阿要注意for的範圍 還有要先取餘不然會爆掉
        for(int k = 2;k<n;k++){
            C[n][k] = (C[n-1][k] + C[n-1][k-1])%10007;
            //printf("n:%d m:%d %d\n",n,k,C[n][k]); //測試用printf 不用在意
        }
    }

    int sum = 1;
    for(int i = 0;i<N;i++){
        if(practices[0][i] != 0 && practices[1][i] != 0){       //x和y有可能是0 會出事所以排除
            sum *= C[practices[0][i]][practices[1][i]];         //把x和y帶入Ｃ求值
            sum %= 10007;       //避免爆開一樣先取餘
        }
    }
    printf("%d\n",sum);
    return 0;
}