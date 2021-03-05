#include <ctype.h>
#include <math.h>
#include <stdio.h>
int solver(int **ptr, int *sum, char *s){
    int i = 0;
    char c = s[i];
    int isNegative = 0,isCounting = 0,tempSum = 0,sumCount = 0;
    int nums[10];
    while(c != '\0'){
        if(isdigit(c)){
            nums[isCounting] = c-'0';
            isCounting++;
        }else if(isCounting){
            
            for(int i = 0;i<isCounting;i++){
                int temp= nums[i]*(int)pow(10,isCounting-1-i);
                tempSum += temp;
                printf("%d\n",temp);
            }
            if(isNegative){
                *ptr[sumCount] = tempSum*(-1);
                *sum += tempSum*(-1);
            }else{
                *ptr[sumCount] = tempSum;
                *sum += tempSum;
            }
            printf("isCounting: %d,isNegative: %d,tempSum: %d\n",isCounting,isNegative,tempSum);
            sumCount++;
            tempSum = 0;
            isNegative = 0;
            isCounting = 0;
        }
        if(c == '-'){
            isNegative = 1;
        }
        i++;
        c = s[i];
    }
    if(isCounting){
            
        for(int i = 0;i<isCounting;i++){
            tempSum += nums[i]*(int)pow(10,isCounting-1-i);
        }
        if(isNegative){
            *ptr[sumCount] = tempSum*(-1);
            *sum += tempSum*(-1);
        }else{
            *ptr[sumCount] = tempSum;
            *sum += tempSum;
        }
        printf("isCounting: %d,isNegative: %d,tempSum: %d\n",isCounting,isNegative,tempSum);
        sumCount++;
    }
    return sumCount;
}