#include <stdio.h>
#include <ctype.h>
int examine(char s[9][9]);
int main(){
    char temp = getchar();
    char sudoku[9][9];
    int isQuestion = 0;
    int finishedInput = 0;
    while(finishedInput < 81){
        if(isdigit(temp) || temp == 'x'){
            sudoku[finishedInput/9][finishedInput%9] = temp;
            finishedInput++;
            //printf("%c ",temp);
        }
        if(temp == 'x')isQuestion = 1;
        temp = getchar();
    }
    //printf("\n");
    /*
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            printf("%c",sudoku[i][j]);
        }
        printf("\n");
    }
    */
    
    if(isQuestion){
        printf("question, ");
    }else{
        printf("solution, ");
    }
    if(examine(sudoku)){
        printf("valid\n");
    }else{
        printf("invalid\n");
    }
    return 0;
}
int examine(char s[9][9]){
    int isValid = 1;
    for(int i = 0;i<9;i++){
        int num[9] = {0,0,0,0,0,0,0,0,0};
        for(int j = 0;j<9;j++){
            //printf("%d %d %d\n",i,j,s[i][j] - '1');
            if(s[i][j] == 'x')continue;
            //printf("%d %d",i,j);
            if(num[s[i][j] - '1']){
                isValid = 0;
                //printf(" NO\n");
                break;
            }else{
                num[s[i][j] - '1'] = 1;
                //printf(" OK\n");
            }
        }
        if(!isValid)break;
    }
    for(int i = 0;i<9;i++){
        if(!isValid)break;
        int num[9] = {0,0,0,0,0,0,0,0,0};
        for(int j = 0;j<9;j++){
            if(s[j][i] == 'x')continue;
            //printf("%d %d",j,i);
            if(num[s[j][i] - '1']){
                isValid = 0;
                //printf(" NO\n");
                break;
            }else{
                num[s[j][i] - '1'] = 1;
                //printf(" OK\n");
            }
        }
    }
    /*
    for(int i = 0;i<3;i++){
        if(!isValid)break;
        for(int j = 0;j<3;j++){
            if(!isValid)break;
            int nums[9] = {0,0,0,0,0,0,0,0,0};
            for(int k = 0;k<3;k++){
                if(!isValid)break;
                for(int l = 0;l<3;l++){
                    if(s[3*i + k][3*j + l]=='x')continue;
                    if(nums[s[3*i + k][3*j + l] - '1']){
                        isValid = 0;
                        //printf(" NO\n");
                        break;
                    }else{
                        nums[s[3*i + k][3*j + l] - '1'] = 1;
                        //printf(" OK\n");
                    }
                }
            }
        }
    }
    */
    return isValid;
}