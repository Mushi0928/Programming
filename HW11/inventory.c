#include <stdio.h>
typedef struct pokemon{
    char name[25];
    int current_HP;
    int max_HP;
    int is_full_health;
}Pokemon;

int compare(int a,int b);

int n;

Pokemon inventory[105];
int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%s %d %d"
            ,inventory[i].name,&inventory[i].current_HP,&inventory[i].max_HP);
        if(inventory[i].current_HP == inventory[i].max_HP){
            inventory[i].is_full_health = 1;
        }else{
            inventory[i].is_full_health = 0;
        }
    }
    for(int i = n-1;i > 0;i--){
        for(int j = 0;j<i;j++){
            //printf("%s : %s ",inventory[j].name,inventory[j+1].name);
            if(compare(j,j+1)){
                //printf("swaped");
                Pokemon temp = inventory[j];
                inventory[j] = inventory[j+1];
                inventory[j+1] = temp;
            }
            //printf("\n");
        }
    }
    for(int i = 0;i<n;i++){
        printf("%s %d %d\n",inventory[i].name,inventory[i].current_HP,inventory[i].max_HP);
    }
    return 0;
}
int compare(int a,int b){
    //a>b return 1,else return 0
    if(inventory[a].is_full_health > inventory[b].is_full_health){
        return 1;
    }else{
        if(inventory[a].current_HP > inventory[b].current_HP){
            return 1;
        }else if(inventory[a].current_HP == inventory[b].current_HP && inventory[a].max_HP > inventory[b].max_HP){
                return 1;
        }
    }
    return 0;
}