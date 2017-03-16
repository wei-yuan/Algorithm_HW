#include <stdio.h>
#include <limits.h>

int Find_Max_Crossing_Subarray(int A[], int low, int mid, int high, int *mlptr, int *mhptr){
	//Left half
	int	sum = 0, left_sum = INT_MIN, right_sum = INT_MIN;

	for (int i= mid; i >= low; i--){
		sum += A[i];
		if(sum > left_sum){
			left_sum  = sum;
			*mlptr  = i; //left_low
		}
		sum = 0; //shouldn't exist, for test
	}

	sum = 0;
	
	//Right half
	for(int j= mid+1; j<=high; j++){
		sum += A[j];
		if(sum > right_sum){
			right_sum  = sum;
			*mhptr = j;   //right_high
		}
		sum = 0; //shouldn't exist, for test
	}
	return (left_sum + right_sum);
}

int Find_Max_Subarray(int A[], int low, int high, int *lptr, int *rptr){
	int mid = 0, left_max = 0, right_max = 0, mid_max = 0;
	int llptr, lhptr, rlptr, rhptr, mlptr, mhptr;
	//Base case: only 1 element
	if(low == high){
		//return low, high, A[low]
		*lptr = low;
		*rptr = low;
		return A[low];
	}
	else{
		mid = (low + high)/2;
		//return max(left,right,middle)
		left_max  = Find_Max_Subarray(A, low, mid, &llptr, &lhptr);
		right_max = Find_Max_Subarray(A, mid+1, high, &rlptr, &rhptr);
		mid_max   = Find_Max_Crossing_Subarray(A, low, mid, high, &mlptr, &mhptr);
		if( left_max >= right_max && left_max >= mid_max ){
			*lptr = llptr;
			*rptr = lhptr;
			return left_max;
		}
		else if( right_max >= left_max && right_max >= mid_max ){
			*lptr = rlptr;
			*rptr = rhptr;
			return right_max;
		}
		else{
			*lptr = mlptr;
			*rptr = mhptr;
			return mid_max;
		}
	}
}

int main(){
	int n;
	int lptr, rptr;

	while( scanf("%d",&n)!= EOF){
		/*input data*/
		int low = 0, high = n-1, max_sum = 0; //fo array
		int A[n]; //an array of pointer to int
		
		for(int i=0;i<n;i++){
			scanf("%d",A+i);
		}
			
		/*Find Max Subarray: divide and conquer - Recursive*/
		max_sum = Find_Max_Subarray(A, low, high, &lptr, &rptr);
		printf("%d %d %d\n", lptr, rptr, max_sum); 
	}
	return 0;
}

