#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

//activity information array
int tmp[4000]  = {0}, info[4000] = {0};
int p[1000]    = {0}, m[1000] 	 = {0}, opt[1000] = {0};    
int fstmp = 0;

int max(int a, int b){int c = (a>b)?a:b; return c;}
void find_sol(int j){   
//	printf("---find_sol---\n");
//	printf("j = %d\n",j);
	if(j != 0){  
		if( *(info+((j-1)*4+3)) + *(m+(*(p+j))) >  *(m+(*p+(j-1)))){   
			*(opt+fstmp) = *(info+((j-1)*4+0)); //real activity 
//			printf("j = %d, OPT[%d] = %d\n",j,fstmp,*(opt+fstmp));						
			fstmp++;
			find_sol(*(p+j));
		}	
		else find_sol(j-1);
	}
}

void merge(int low, int high /*, int *lptr, int *rptr*/){  //Divide and conquer
	int i = low-1, mid = low + (high-low)/2;
	int ll =low-1, lh = mid-1, rl = mid, rh = high-1; // ll-> left low, lh -> left high
//	printf("---Merge---\n");
//	printf("left= %d, right=%d, i =%d\n",low,high,i);
	if(low >= high)return;

	while(ll<=lh && rl<=rh){ //watch out: low, high is activity number
		//*(tmp+(i++)) = *(info+((ll-1)*4+2)) < *(info+((rl-1)*4+2)) ? *(info+((ll-1)*4)) : *(info+((rl-1)*4));
		if( *(info+(ll*4+2)) < *(info+(rl*4+2)) ){   //left end time < right end time
			for(int j=0; j<4; j++){*(tmp+(i*4+j)) = *(info+(ll*4+j));}
			i++;
			ll++;
		}
		else{   //  <  case
			for(int j=0; j<4; j++){*(tmp+(i*4+j)) = *(info+(rl*4+j));}				
			i++;
			rl++;			
		}		
	}
	while(ll <= lh){
		for(int j=0;j<4;j++){*(tmp+(i*4+j)) = *(info+(ll*4+j));}
		i++;		
		ll++;		
	}
	while(rl <= rh){
		for(int j=0;j<4;j++){*(tmp+(i*4+j)) = *(info+(rl*4+j));}
		i++;
		rl++;		
	}
	for(int j=0;j< high;j++){
		for(int k=0;k<4;k++){*(info+(j*4+k)) = *(tmp+(j*4+k));}
	}
}

void mergesort(int low, int high){   
	int mid;
//	printf("---Merge Sort---\n");
//	printf("low =%d, high= %d\n", low, high);
	mid = (low+high)/2; //mid是integer, 小數點自動捨去
	if(low < high){
		mergesort(low,mid); 		//left half
		mergesort(mid+1,high); 	//right half
		merge(low,high);
	}
}

int main(){   
	int set=0, act=0, num_set = 0, num_act = 0; //read activity
	int low, high;
	int max_total_value = 0;

	printf("plz input how many set of test case\n");
	scanf("%d",&num_set);
//	printf("num_act = %d\n",num_set);

	for(int i=0;i<num_set;i++){
		printf("plz input how many activites\n");
		scanf("%d",&num_act);
//		printf("num_act = %d\n",num_act);

		while(1){
			//readline
			for(int i=0;i<num_act;i++)scanf("%d %d %d %d", info+(0+i*4), info+(1+i*4), info+(2+i*4), info+(3+i*4)); //scanf("%d",A+i)
			//check result
//			for(int i=0;i<num_act;i++)printf("%d %d %d %d\n",*(info+(0+i*4)), *(info+(1+i*4)), *(info+(2+i*4)), *(info+(3+i*4)));

			//Sorting by end time
			low  = *(info+0);
			high = *(info+(0 + (num_act-1)*4));
//			printf("low =%d, high = %d, (mum_act-1)*4 =%d\n", low, high, (num_act-1)*4);			
			mergesort(low,high);				

			//activity selection problem DP
			//V -> Value, already in info[i*4+3]
			//P[ ] nearest non-overlapping activity
			for(int i=0;i<num_act;i++){
				if(i != 0){
					if(*(info+(i*4+1)) > *(info+((i-1)*4+2))){ //check if overlapping or not
						p[i+1] = i;
//						printf("p[i+1 =%d] = %d(i)",i+1,i);
					}	
					else{  
						for(int j=i;j>0;j--){
							if(*(info+(i*4+1)) > *(info+((j-2)*4+2))){ //check if overlapping or not
								if(j-2 >= 0){
									p[i+1] = j-1;
//									printf("p[i+1 =%d] = %d(j-1)",i+1,j-1);
									break;
								}
								else break;
							}		
						}
					}
				}
				for(int j=0;j<4;j++){					
					printf("info[%d] =%d\n",i*4+j,info[i*4+j]);
				}				
			}			
			for(int i=0;i<=num_act;i++){
				printf("p[%d] =%d\n",i,p[i]);
			}
			//M[ ] array
			int opt_cnt = 0;
			for(int i=0;i<=num_act;i++){   
				m[i] = max( (*(info+((i-1)*4+3)) + m[p[i]]), m[i-1]);
			}

			//find_sol
			printf("num_act =%d\n", num_act);
			find_sol(num_act);
			
			for(int i=0;i<=num_act;i++){   
				m[i] = max( (*(info+((i-1)*4+3)) + m[p[i]]), m[i-1]);
				printf("P[%d] =%d, M[%d] = %d, OPT[%d] =%d\n",i,*(p+i),i,*(m+i),i,*(opt+i));
			}
			//Sorting activity for final answer
						
			printf("%d\n",m[num_act]);// final max value
			//escape
			set++;
//			printf("set =%d, num_set= %d\n",set,num_set);
			if(set == num_set){
				printf("break out of while");
				break;
			}
		} //while()
		set		= 0;
		num_act = 0;
	}//for()
}
