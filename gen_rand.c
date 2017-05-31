#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){  
	srand(time(NULL));
	//rand() % (max_number + 1 - minimum_number) + minimum_number
	int n = rand() % (100+1-1) + 1; //act = 1~5
	int s /*= rand()% (100+1-1) + 0*/; //start time  = 0~100
	int f /*= rand()% (100+1-1) + 1*/; //finish time = 1~100
	int v /*= rand()% (100+1-(-100)) + (-100)*/; //value = -100~100

	for(int i = 1; i<=1000; i++){  
		s = rand()% (100+1-1) + 0;
		f = rand()% (100+1-1) + 1;
//		v = rand()% (100+1-(-100)) + (-100);
		if( s<= f){
//			printf("%d %d %d %d\n",i,s,f,v);
			printf("%d %d %d %d\n",i,1,1,1);
		}
		else{
//			printf("%d %d %d %d\n",i,s,s,v);
			printf("%d %d %d %d\n",i,1,1,1);
		}
	}
	return 0;
}
