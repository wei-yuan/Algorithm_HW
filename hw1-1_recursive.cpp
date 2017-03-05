#include <cstdio>
#include <cstdlib>
#include <math.h>

int Find_Max_Subarray(int A[n],int low,int high){
	if(low == high)
		printf("%d %d %d",low,low,A[low]);
	else{
		mid = floor(low+high/2);
		Find_Max_Subarray(A[n],low,mid);  //Left half
		Find_Max_Subarray(A[n],mid,high); //Right half	
		Find_Max_Crossing_Subarray(A[n],low,mid,high);
		if(left_sum >= mid_sum && left_sum >= right_sum)
		//	return left_low, left_high, left_sum
		//	printf("%d %d %d",left_low,left_high,left_sum);
		if(right_sum >= mid_sum && right_sum >= left_sum)
		//	return right_low, right_high, right_sum
		//	printf("%d %d %d",right_low,right_high,right_sum);
		else
		//	return mid_low, mid_high, mid_sum
		//	printf("%d %d %d",mid_low,mid_high,mid_sum);
	}
}

int Find_Max_Crossing_Subarray(int A[n],int low,int mid, int high){
	//Left Sum
	int mid_low, mid_high, mid_sum;
	int left_low, left_high, sum = 0,last_term_sum = 0, left_sum = -1000000;
	
	for (int i=low; i<=mid; i++){
		for(int j=i; j<=mid; j++){
			sum += A[j];
			if(j == mid)
				last_term_sum = sum; // Save data only when j reach mid
		}	
		if(last_term_sum > left_sum){
			left_sum  = last_term_sum;
			left_low  = i;
			left_high = mid;
		}
		last_term_sum = 0;
		sum = 0;
	}

	//Right Sum
	sum = 0;
	int right_low, right_high, right_sum = -1000000;
	for(int i=high;i >= mid; i++){
		for(int j=i; j>=mid; j--){
			sum += A[j];
			if( j == mid)
				last_term_sum = sum; // Save data only when j reach mid
		}		
		if(last_term_sum > right_sum){
			right_sum  = last_term_sum;
			right_low  = mid;
			right_high = j;									
		}
		sum = 0;	
	}

	mid_low  = left_low;
	mid_high = right_high;
	mid_sum  = left_sum + right_sum;
	//return mid_low,mid_high,mid_sum;
	//printf("%d %d %d",mid_low,mid_high,mid_sum);
}

int main(){
	int n;

	while(1){
		/*input data*/
		scanf("%d",&n);
		
            	//Input data specification
		if( n<1 || n >= 100000 ) 
			break;

		int low,high,flag = 0, minus = 0;
		int A[n];
		
		for(int i=0;i<n;i++){
			scanf("%d",&A[i]);
			if(A[i] > 100000)
				flag = 1;
                        if(A[i] < 0)
				minus++;
		}
		
		//Check if there is A[i] > 100000
		if(flag == 1 || minus == n)
			break;
		


		//Find Max Subarray: divide and conquer
		Find_Max_Subarray(A[n],low,high);
	}
	return 0;
}
