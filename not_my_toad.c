#include<stdio.h>
#include<stdlib.h>

int n, s, t, energy_max = 0, step_max = 0;
int h[100005] = {0}, c[20] = {0};
int route[10000000] = {0};
int consume(int step){

	for(int i = 0;i<=step;i++){
		printf("%d ",route[i]);
	}
	printf("\n");

	int energy = 0;
	for(int i=1; i<=step; i++){
		if(h[route[i]]>h[route[i-1]]&&(route[i]>route[i-1])) energy = energy+((h[route[i]]-h[route[i-1]])*(route[i]-route[i-1]));
		else if(h[route[i]]<h[route[i-1]]&&(route[i]>route[i-1])) energy = energy+((h[route[i-1]]-h[route[i]])*(route[i]-route[i-1]));
		else if(h[route[i]]>h[route[i-1]]&&(route[i]<route[i-1])) energy = energy+((h[route[i]]-h[route[i-1]])*(route[i-1]-route[i]));
		else energy = energy+((h[route[i-1]]-h[route[i]])*(route[i-1]-route[i]));
	} 
	return energy;
}
void jump(int cur, int end, int step){
	if(cur==end){
		int energy = consume(step);
		if(energy>energy_max){
			energy_max = energy;
			step_max = step;
		}
		else if(energy==energy_max&&step>step_max){
			step_max = step;
		}
	}
	else{
		int flag = 1;
		for(int i=1-cur; i<=n-cur; i++){
			flag = 1;
			if(i!=0){
				
				for(int j=0; j<=step; j++){
					if((cur+i)==route[j]) flag = 0;
					printf("cur+1: %d route[j]: %d\n",cur+i,route[j]);
					break;
				}
				printf("current: %d,current+i: %d,c[cur]: %d,c[cur+i]: %d,flag: %d\n",cur,cur+i,c[cur],c[cur+i],flag);
				if(((c[cur+i]==c[cur])|| (i==1) || (i==-1) ) && flag==1){
					route[step+1] = cur+i;
					jump(cur+i, end, step+1);
					route[step+1] = 0;
				}
			}
		}
	}
	return;
}
int main(void){
	scanf("%d %d %d", &n, &s, &t);
	for(int i=1; i<=n; i++){
		scanf("%d", &h[i]);
	}
	for(int i=1; i<=n; i++){
		scanf("%d", &c[i]);
	}
	route[0] = s;
	jump(s, t, 0);
	printf("%d %d\n", energy_max, step_max);
	return 0;
} 
