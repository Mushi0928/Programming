#include "function.h"
AccountData* createData(char* name, int money){
    AccountData* temp = (AccountData*)malloc(sizeof(AccountData));
    char* string = (char*)malloc(100*sizeof(char));
    strcpy(string,name);
    temp->name = string;
    temp->money = money;
    return temp;
}
AccountData* userQuery(AccountData* data){
    AccountData* temp = (AccountData*)malloc(sizeof(AccountData));
    char* string = (char*)malloc(100*sizeof(char));
    strcpy(string,data->name);
    temp->name = string;
    return temp;
}