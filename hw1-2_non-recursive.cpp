#include <cstdio>
#include <cstdlib>

int main(){
    int n;
    /*Input Data iteratively*/
    while( scanf("%d",&n) != EOF ){
        //Input data specification
		if( n<1 || n >= 100000 ) 
			break;

		int low,high,flag = 0,minus = 0,sum = 0,max_sum = -1000000;
		int A[n];
		
		for(int i=0;i<n;i++){
			scanf("%d",&A[i]);
			if(A[i] > 100000)
				flag = 1;
                                   if(A[i] < 0)
				minus++;
		}
		
		//Check if there is A[i] > 100000
		if(flag == 1 || minus == n){
			printf("0 0 0");
			break;
		}		
	    
		/*Moving Sliding Window*/
		for(int i=0;i<n;i++){
			/*Summation*/	
			for(int j=i;j<n;j++){ 
				sum += A[j];
				if(sum > max_sum){
					max_sum = sum;
					low	= i;
					high	= j;
				}
			}	
			sum = 0; 
		}

		/*Printing Result*/
		printf("%d %d %d",low,high,max_sum);
		printf("\n"); // next line: for Online Judge
	}
	return 0; //return value: for int main function
}

