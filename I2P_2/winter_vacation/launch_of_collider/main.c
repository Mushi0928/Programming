#include <stdio.h>

int n;
char direction[200001];
int coord[200001];
int minTime = __INT_MAX__;

int main(){
    scanf("%d",&n);
    scanf("%s",direction);
    for(int i = 0;i<n;i++){
        scanf("%d",&(coord[i]));
    }
    for(int i = 0;i<n-1;i++){
        if(direction[i] == 'R' && direction[i+1] == 'L'){
            int time = (coord[i+1] - coord[i])/2;
            if(time < minTime)minTime = time;
        }
    }
    if(minTime == __INT_MAX__)printf("-1\n");
    else printf("%d\n",minTime);
    return 0;
}