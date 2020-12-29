#include <stdio.h>
#include <stdlib.h>
#include "function.h"

char s[100];
int money, attack_money;
AccountData* data;
int main(){

    // store money in bank
    scanf("%s",s);
    scanf("%d",&money);
    scanf("%d",&attack_money);
    getchar(); // ignore newline
    AccountData* data = createData(s, money);

    // copy data and let user to query (handle process in bank)
    AccountData* userData = userQuery(data);

    // evil person try to attack
    userData->money = attack_money;

    // the money in bank
    printf("---money in bank---\nname: %s\nmoney: %d\n",data->name, data->money);
    if(data->money != userData->money){
        printf("warning! the user is try to modify the money in bank to %d\n",userData->money);
    }else{
        printf("query finish\n");
    }

    // free data
    free(userData->name);
    free(userData);
    free(data->name);
    free(data);
    return 0;
}