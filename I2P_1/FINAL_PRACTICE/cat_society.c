#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
    elder,
    nursy,
    kitty,
    warrior,
    apprentice,
    medicent,
    deputy,
    leader,
*/
typedef struct _Cat{
    char* name;
    int occupation;
    int age;
}Cat;

Cat* cats;
int N,M;

int main(){
    while(~scanf("%d %d",&N,&M)){
        cats = (Cat*)malloc(N*sizeof(Cat));
        for(int i = 0;i<N;i++){
            char* name = (char*)malloc(35*sizeof(char));
            char occu[15];
            scanf("%s %s %d",name,occu,cats[i].age);
            switch(occu[0]){
                case 'e':
                    cats[i].occupation = 0;
                    break;
                case 'n':
                    cats[i].occupation = 1;
                    break;
                case 'k':
                    cats[i].occupation = 2;
                    break;
                case 'w':
                    cats[i].occupation = 3;
                    break;
                case 'a':
                    cats[i].occupation = 4;
                    break;
                case 'm':
                    cats[i].occupation = 5;
                    break;
                case 'd':
                    cats[i].occupation = 6;
                    break;
                case 'l':
                    cats[i].occupation = 7;
                    break;
            }
        }
    }
}
