#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

//activity information array
int tmp[4000]  = {0}, info[4000] = {0};
int p[1000]    = {0}, m[1000] 	 = {0}, opt[4000] = {0};    
int fstmp = 0;

int max(int a, int b){return (a>b)?a:b;}
void find_sol(int j){   
//	printf("---find_sol---\n");
//	printf("j = %d\n",j);
	if(j<=0)return; // j<= 0, escape recursion
	else if( *(info+((j-1)*4+3)) + *(m+(*(p+j))) >  *(m+(*p+(j-1)))){   
		for(int i=0; i<4; i++){   
			*(opt+(fstmp*4+i)) = *(info+((j-1)*4+i)); //real activity
		}
		fstmp++;
		find_sol(*(p+j));
	}	
	else find_sol(j-1);
}

void merge(int sort[], int tmp[], int low, int high, int *cptr /*, int *lptr, int *rptr*/){  //Divide and conquer
	int i = low-1, mid = low + abs(high-low)/2;
	int ll =low-1, lh = mid-1, rl = mid, rh = high-1; // ll-> left low, lh -> left high
//	printf("---Merge---\n");
//	printf("low =%d, mid =%d, high= %d, \n", low, mid, high);
//	printf("ctrl= %d\n",*cptr);
	if(low >= high)return;
	while(ll<=lh && rl<=rh){ //watch out: low, high is activity number
		if( *(sort+(ll*4+ *cptr )) < *(sort+(rl*4+ *cptr )) ){   //left end time <= right end time
			for(int j=0; j<4; j++){*(tmp+(i*4+j)) = *(sort+(ll*4+j));}			
			i++;
			ll++;
		}
		else if( *(sort+(ll*4+ *cptr )) == *(sort+(rl*4+ *cptr )) ){   
			if(*(sort+(ll*4+1)) <= *(sort+(rl*4+1))){ //left start time <= right start time
				for(int j=0; j<4; j++){*(tmp+(i*4+j)) = *(sort+(ll*4+j));}
				i++;
				ll++;
			}
			else{   
				for(int j=0; j<4; j++){*(tmp+(i*4+j)) = *(sort+(rl*4+j));}
				i++;
				rl++;
			}			
		}		
		else{   //  <  case
			for(int j=0; j<4; j++){*(tmp+(i*4+j)) = *(sort+(rl*4+j));}				
			i++;
			rl++;			
		}		
	}
	while(ll <= lh){
		for(int j=0;j<4;j++){*(tmp+(i*4+j)) = *(sort+(ll*4+j));}
		i++;		
		ll++;		
	}
	while(rl <= rh){
		for(int j=0;j<4;j++){*(tmp+(i*4+j)) = *(sort+(rl*4+j));}
		i++;
		rl++;		
	}
	for(int j=0;j< high;j++){
		for(int k=0;k<4;k++){
			*(sort+(j*4+k)) = *(tmp+(j*4+k));
		}
	}		
}

void mergesort(int sort[], int tmp[], int low, int high, int *cptr){   
	int mid;
//	printf("---Merge Sort---\n");
//	printf("low =%d, high= %d\n", low, high);
	mid = low + abs(high-low)/2; //mid是integer, 小數點自動捨去
	if(low < high){
		mergesort(sort,tmp,low,mid,cptr); 		//left half
		mergesort(sort,tmp,mid+1,high,cptr); 	//right half
		merge(sort,tmp,low,high,cptr);
	}
}

int main(){   
	int num_set = 0, num_act = 0; //read activity
	int low, high;
	
	scanf("%d",&num_set);
	for(int i=0;i<num_set;i++){
		scanf("%d",&num_act);
		while(1){
			int ctrl = 2; // 2-> finish time, 0 -> activity number		
			int *cptr = &ctrl;
			//readline
//			printf("num_act =%d\n",num_act);
			for(int i=0;i<num_act;i++){
				scanf("%d %d %d %d", info+(i*4+0), info+(i*4+1), info+(i*4+2), info+(i*4+3)); //scanf("%d",A+i)
			}
			//Sorting by end time //low <-> high ???
			low  = 1; //*(info+0); //1
			high = num_act;//*(info+(0 + (num_act-1)*4)); //
			mergesort(info,tmp,low,high,&ctrl);				
			//sorted array
//			printf("---check opt---\n");
			printf("---Info sort by finish time---\n");
			for(int i =0;i< num_act; i++){   
	//			for(int j =0;j<4;j++)
					//printf("opt[%d] = %d, opt[%d] = %d, opt[%d] = %d, opt[%d] = %d\n", i*4+0, *(opt+(i*4+0)), i*4+1, *(opt+(i*4+1)), i*4+2, *(opt+(i*4+2)), i*4+3, *(opt+(i*4+3)));
					printf("info[%d] = %d, info[%d] = %d, info[%d] = %d, info[%d] = %d\n", i*4+0, *(info+(i*4+0)), i*4+1, *(info+(i*4+1)), i*4+2, *(info+(i*4+2)), i*4+3, *(info+(i*4+3)));
			}
			
			//activity selection problem DP
			//P[ ] nearest non-overlapping activity
			for(int i=1; i< num_act; i++){
				if(*(info+(i*4+1)) >= *(info+((i-1)*4+2))){ // if i start time >= i-1 finish time. no overlapping
					p[i+1] = i;
				}	
				else{  
					for(int j=i;j>0;j--){
						if(j > 1){
							if(*(info+(i*4+1)) >= *(info+((j-2)*4+2))){ 
								if(j-2 >= 0){
									p[i+1] = j-1;
									break; //break for
								}
							}	
						}
						else p[i+1] = 0; //num_act = 2, if no compatible set, set p[2] = 0;
					}
				}
			}			
			//M[ ] array
			for(int i=1;i<=num_act;i++){   
				*(m+i) = max(  *(info+((i-1)*4+3)) + *(m+(*(p+i))), *(m+(i-1)) );// 3: value

			}
			//find_sol
			find_sol(num_act);
			
			for(int i=0;i<=num_act;i++){   
				printf("v[%d] =%d, p[%d] =%d, m[%d]= %d, m[%d] = %d, fstmp =%d\n", i, *(info+((i-1)*4+3)), i, *(p+i), p[i], m[p[i]],i, *(m+i), fstmp);
			}
			
/*			for(int i =0;i< num_act; i++){   
				printf("opt[%d] = %d, opt[%d] = %d, opt[%d] = %d, opt[%d] = %d\n", i*4+0, *(opt+(i*4+0)), i*4+1, *(opt+(i*4+1)), i*4+2, *(opt+(i*4+2)), i*4+3, *(opt+(i*4+3)));
			}
*/

			//Sorting by activity
			low  = 1;      //fisrt term of sol array
			high = fstmp;  //last term of sol array
			ctrl = 0; //switch to 0:activity
//			printf("act opt low=%d, high= %d, ctrl =%d, fstmp =%d", low, high, ctrl, fstmp);
			mergesort(opt,tmp,low,high,&ctrl);
/*			printf("---opt sort by activity---\n");
			for(int i =0;i< fstmp; i++){   
				printf("opt[%d] = %d, opt[%d] = %d, opt[%d] = %d, opt[%d] = %d\n", i*4+0, *(opt+(i*4+0)), i*4+1, *(opt+(i*4+1)), i*4+2, *(opt+(i*4+2)), i*4+3, *(opt+(i*4+3)));
			}
*/			
			printf("num_act = %d\n",num_act);
			printf("%d\n",m[num_act]);// final max value

			if(m[num_act] == 0) 
				printf("0\n");
			for(int i=0;i<fstmp;i++){
				printf("%d",*(opt+(i*4)));
				if(i == fstmp-1){
					printf("\n");
					break; //break out for loop
				}
				printf(" ");
			}				
			
			//escape
//			printf("i =%d, set =%d, num_set= %d, num_act = %d\n",i,set,num_set,num_act);			
//				printf("break out of while\n");
				break;
		} //while()
//		if(i < num_act-1){ //最後一次不需要清空
//			printf("---Clear---\n");
			num_act = 0;
			fstmp = 0;			
			for(int i= 0; i < 4000; i++){
				*(tmp+i) = 0; 
				*(info+i)= 0; 
				*(opt+i) = 0;    
			}
			for(int i= 0; i < 1000; i++){
		        *(p+i) = 0;
				*(m+i) = 0;
			}	
	//		}
	}//for()
	return 0;
}
