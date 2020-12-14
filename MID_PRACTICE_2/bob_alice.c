#include <stdio.h>
#include <string.h>

int samePattern(char S[]);

char P[5005];
int p_len,N;

int main(){
    scanf("%d %s",&N,P);
    p_len = strlen(P);
    char str[N][5005];
    int freq[N];
    int flag = 0;
    char temp[5005];
    for(int i = 0;i<N;i++){
        scanf("%s",temp);
        if(strlen(temp) == p_len){
            if(flag != 0 && strcmp(temp,str[flag-1]) == 0){
                freq[flag-1]++;
            }else if(samePattern(temp)){
                strcpy(str[flag],temp);
                freq[flag]++;
                flag++;
            }
        }
    }
    printf("%d\n",flag);
    for(int i = flag-1;i>0;i--){
        for(int j = 0;j<i;j++){
            if(freq[j] < freq[j+1] || (freq[j] == freq[j+1] && strcmp(str[j],str[j+1]) > 0)){
                char tempS[5005];
                strcpy(tempS,str[j]);
                strcpy(str[j],str[j+1]);
                strcpy(str[j+1],tempS);

                int tempF = freq[j];
                freq[j] = freq[j+1];
                freq[j+1] = tempF;
            }
        }
    }
    for(int i = 0;i<flag;i++){
        printf("%s %d\n",str[i],freq[i]);
    }
    return 0;
}
int samePattern(char S[]){
    char map[130] = { 0 };
    int used[130] = { 0 };
    for(int i = 0;i<p_len;i++){
        //printf("%d %d",map[P[i]],S[i]);
        if(map[P[i]] == 0 && !used[S[i]]){
            map[P[i]] = S[i];
            used[S[i]] = 1;
        }else if(map[P[i]] != S[i]){
            //printf("%s not same\n",S);
            return 0;
        }
    }
    //printf("%s same\n",S);
    return 1;
}