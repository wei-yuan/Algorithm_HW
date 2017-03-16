#include <stdio.h>  
#include <math.h>  
  
int max_crossing_subarray(int array[], int *low, int mid, int *high)  
{  
    int left_sum = (int)-INFINITY;  
    int max_left = mid;  
    for (int i = mid, sum = 0; i >= *low; i--) {  
        sum += array[i];  
        if (sum > left_sum) {  
            left_sum = sum;  
            max_left = i;  
        }  
    }  
  
    int right_sum = (int)-INFINITY;  
    int max_right = mid;  
    for (int i = mid + 1, sum = 0; i <= *high; i++) {  
        sum += array[i];  
        if (sum > right_sum) {  
            right_sum = sum;  
            max_right = i;  
        }  
    }  
  
    *low = max_left;  
    *high = max_right;  
    return left_sum + right_sum;  
      
}  
  
int max_subarray(int array[], int *low, int *high)  
{  
    if (*low == *high) {  
        return array[*low];  
    } else {  
        int mid = *low + (*high - *low)/2;  
  
        int left_low = *low;  
        int left_high = mid;  
        int left_sum = max_subarray(array, &left_low, &left_high);  
  
        int right_low = mid + 1;  
        int right_high = *high;  
        int right_sum = max_subarray(array, &right_low, &right_high);  
  
        int cross_low = *low;  
        int cross_high = *high;  
        int cross_sum = max_crossing_subarray(array, &cross_low, mid, &cross_high);  
  
        if (left_sum >= right_sum && left_sum >= cross_sum)  
        {  
            *low = left_low;  
            *high = left_high;  
            return left_sum;  
  
        } else if (right_sum >= left_sum && right_sum >= cross_sum) {  
            *low = right_low;  
            *high = right_high;  
            return right_sum;  
  
        } else {  
            *low = cross_low;  
            *high = cross_high;  
            return cross_sum;  
        }  
    }  
}  
  
  
int main()  
{  
    /* 
    int array[5] = {-13, -3, -25, -20, -2}; 
    int low = 0; 
    int high = sizeof(array)/sizeof(int) -1; 
    */  
    int n;  
    //char t;  
    //scanf("%d%c", &n, &t);  
    //scanf("%d", &n);  
    //printf("1st %d %d\n", n, t);  
    while(scanf("%d", &n) != EOF)//(c = getchar()) != '\n' && c != EOF  
    {  
        //if((n > 100000) || (n < 1)) break;  
          
        int array[n];  
        for(int i = 0; i<n; i++)  
        {  
            scanf("%d", array+i);  
        }  
        int low = 0;  
        int high = n-1;  
          
  
        //printf("low %d, high %d\n", low, high);  
        printf("%d %d %d\n", low, high, max_subarray(array, &low, &high));  
        //printf("low %d, high %d\n", low, high);  
        //scanf("%d%c", &n, &t);  
  
    }  
    return 0;  
}  
