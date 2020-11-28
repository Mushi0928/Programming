#include <stdio.h>

int main(){
    int R,C,T;
    scanf("%d %d %d",&R,&C,&T);

    char classroom[100][100];

    for(int i = 0;i<R;i++){
        for(int j = 0;j<C;j++){
            char temp;
            scanf("%c",&temp);
            if(temp != '\n'){
                classroom[i][j] = temp;
            }else{
                j--;
            }
        }
    }

    for(int i = 0;i<T;i++){
        int changed[R][C];
        for(int i = 0;i<R;i++){
            for(int j = 0;j<C;j++){
                changed[i][j] = 0;
            }
        }
        for(int j = 0;j<R;j++){
            for(int k = 0;k<C;k++){
                if(classroom[j][k] == 'F'){
                    if(classroom[j+1][k] == 'C'){
                        changed[j+1][k] = 1;
                    }
                    if(classroom[j-1][k] == 'C'){
                        changed[j-1][k] = 1;
                    }
                    if(classroom[j][k+1] == 'C'){
                        changed[j][k+1] = 1;
                    }
                    if(classroom[j][k-1] == 'C'){
                        changed[j][k-1] = 1;
                    }
                }
            }
        }
        for(int j = 0;j<R;j++){
            for(int k = 0;k<C;k++){
                if(changed[j][k]){
                    classroom[j][k] = 'F';
                }
            }
        }
    }

    for(int l = 0;l<R;l++){
        for(int p = 0;p<C;p++){
            printf("%c",classroom[l][p]);
        }
        printf("\n");
    }
    

    return 0;
}