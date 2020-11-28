#include <stdio.h>

int main(){
    char encrypted[1000],decrypted[1000];       //宣告存字串的陣列
    int enc_alphabet[26],dec_alphabet[26];      //宣告紀錄字母組成的陣列
    int enc_length,dec_length;      //宣告存字串長度的變數
    while(scanf("%d %d %s %s",&enc_length,&dec_length,encrypted,decrypted) != EOF){
        if(enc_length != dec_length){       //如果字串長度不一樣就直接NO了 然後進入下一個迴圈
            printf("NO\n");
            continue;
        }
        for(int i = 0;i<26;i++){        //將紀錄字母組成的陣列全部設成0
            enc_alphabet[i] = 0;
            dec_alphabet[i] = 0;
        }
        for(int i = 0;i<enc_length;i++){        //紀錄字母組成
            enc_alphabet[ encrypted[i]-'a' ] ++;        //將紀錄字母組成陣列的第(字串第i項 - a)項 +1
            dec_alphabet[ decrypted[i]-'a' ] ++;
        }
        int result = 1;
        for(int i = 0;i<26;i++){        //比對兩個字母組成陣列的每一項是否相等
            if(enc_alphabet[i] != dec_alphabet[i]){
                result = 0;
                break;
            }
        }
        if(result){     //printf結果
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
}