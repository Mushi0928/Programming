#include <stdio.h>

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int operations[m];
    int nums[n];
    for(int i = 0;i<n;i++){
        nums[i] = 0;
    }
    for(int i = 0;i<m;i++){
        int temp;
        scanf("%d",&temp);
        operations[i] = temp;
        if(nums[temp-1] == 0){
            nums[temp-1] = 1;
        }
    }
    for(int i = m-1;i>=0;i--){
        if(nums[operations[i]-1] == 1){
            printf("%d\n",operations[i]);
            nums[operations[i]-1] = -1;
        }
    }
    for(int i = 0;i<n;i++){
        if(nums[i] == 0){
            printf("%d\n",i+1);
        }
    }


}