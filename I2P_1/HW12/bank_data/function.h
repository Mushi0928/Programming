#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _AccountData {

	char* name;

	int money;

} AccountData;
AccountData* createData(char* name, int money);
AccountData* userQuery(AccountData* data);