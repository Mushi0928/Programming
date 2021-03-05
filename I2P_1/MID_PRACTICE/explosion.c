#include <stdio.h>
#include <string.h>

int main(){
    int T;
    
    int str1_len,str2_len;

    scanf("%d",&T);     //scan有幾筆測資
    for(int i = 0;i<T;i++){     
        char str1[1000] ,str2[1000];    //scan兩個string進來然後取得長度
        scanf("%s %s",str1,str2);
        str1_len = strlen(str1);
        str2_len = strlen(str2);
        
        int Len;
        if(str1_len>str2_len){      //比較兩個string的長度決定最多要檢查到幾位
            Len = str2_len;
        }else{
            Len = str1_len;
        }

        int validLength = 0;    //最大可消掉的長度
        for(int j = 1;j <= Len;j++){    //測試能不能消掉的過程
            int valid = 1;
            for(int k = 0;k<j;k++){
                if(str1[str1_len - j + k] != str2[k]){
                    valid = 0;
                    break;
                }
            }
            if(!valid)continue;
            validLength = j;
        }

        printf("%s",str1);      //print最後的結果
        for(int l = validLength;l<str2_len;l++){
            printf("%c",str2[l]);
        }
        printf("\n");
    }
    return 0;
}