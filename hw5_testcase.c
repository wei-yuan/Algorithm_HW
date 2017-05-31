#include <stdio.h>

int main(){  
	int n = 1000;
	printf("%d\n",1);		
	printf("%d\n",1000);
	printf("%d\n",999000);
	for(int j=0;j<n;j++){
		/*printf("%d\n",1000);
		printf("%d\n",999000);*/
		for(int i=0;i<n;i++){
			if( i != j){
				printf("%d %d\n",i,j);
			}
		}	
	}
	return 0;
}
