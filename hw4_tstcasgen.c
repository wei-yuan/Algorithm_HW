#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){ 
	T[1000];
	srand(time(NULL));
	int n = rand() % (1000 +1 -1) + 1;
	int g1 = rand() % (1000 +1 -1) + 1;
	int g2 = rand() % (1000 +1 -1) + 1;
	int f = rand() % (1000 +1 -1) + 1;
	
	for(int i=1;i<=1000;i++){
		printf("M %d\n",i);	
	}
	for(int i=1;i<=n;i++){
		g1 = rand() % (1000 +1 -1) + 1;
		g2 = rand() % (1000 +1 -1) + 1;
		if(T[g1-1] == 0){   
			
		}
		else{   
		}
		printf("G %d %d\n",g1,g2);
	}
	for(int i=1;i<=n;i++){
		f = rand() % (1000 +1 -1) + 1;
		printf("F %d\n",f);			
	}
	printf("E\n");
	return 0;
}
