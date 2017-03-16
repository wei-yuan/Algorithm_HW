#include <stdio.h>
#include <limits.h>

int main(){
    int n;
    /*Input Data iteratively*/
    while( scanf("%d",&n) != EOF ){
		int A[n];
		int low = 0,high = 0,tmp = 0,sum = 0,max_sum = INT_MIN;
		
		for(int i=0;i<n;i++){
			scanf("%d",A+i);
		}
		 
		/*Moving Sliding Window*/
		for(int i=0;i<n;i++){
			//Summation	
				sum += A[i];
				if(sum < 0){
					sum = 0;
					tmp = i+1;	
				}	
				if(sum > max_sum){
					max_sum = sum;
					low = tmp;
					high = i;
				}
		}
	
		/*Printing Result*/
		printf("%d %d %d\n",low,high,max_sum);
	}
	return 0; //return value: for int main function
}

