#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1000 

int T[MAX][MAX][2] = {}, tmp[MAX][3] = {}, edge[MAX][3] = {}, A[MAX] = {}, column = 3, wc_num = 3, set =0, opy_num = 0, nd1 = 0, nd2 = 0, w = 0, total_weight = 0; //opt_num: option, column: merge sort column #, wc: weight column #

// for read line
char *line = NULL;
size_t len = 0;	  //unsigned
ssize_t read = 0; //signed

void merge(int sort[], int tmp[], int low, int high/*, int *cptr*/ ){  //Divide and conquer
	int i = low-1, mid = low + abs(high-low)/2, ll =low-1, lh = mid-1, rl = mid, rh = high-1; // ll-> left low, lh -> left high
	if(low >= high)return;
	while(ll<=lh && rl<=rh){ //watch out: low, high is activity number
		if( *(sort+(ll*column+ wc_num )) < *(sort+(rl*column+ wc_num )) ){   //left end time <= right end time
			for(int j=0; j<column; j++){*(tmp+(i*column+j)) = *(sort+(ll*column+j));}			
			i++;
			ll++;
		}
		else if( *(sort+(ll*column+ wc_num )) == *(sort+(rl*column+ wc_num )) ){   
			if(*(sort+(ll*column+1)) <= *(sort+(rl*column+1))){ //left start time <= right start time
				for(int j=0; j<column; j++){*(tmp+(i*column+j)) = *(sort+(ll*column+j));}
				i++;
				ll++;
			}
			else{   
				for(int j=0; j<column; j++){*(tmp+(i*column+j)) = *(sort+(rl*column+j));}
				i++;
				rl++;
			}			
		}		
		else{   //  <  case
			for(int j=0; j<column; j++){*(tmp+(i*column+j)) = *(sort+(rl*column+j));}				
			i++;
			rl++;			
		}		
	}
	while(ll <= lh){
		for(int j=0;j<column;j++){*(tmp+(i*column+j)) = *(sort+(ll*column+j));}
		i++;		
		ll++;		
	}
	while(rl <= rh){
		for(int j=0;j<column;j++){*(tmp+(i*column+j)) = *(sort+(rl*column+j));}
		i++;
		rl++;		
	}
	for(int j=0;j< high;j++)
		for(int k=0;k<column;k++){*(sort+(j*column+k)) = *(tmp+(j*column+k));}	
}
void mergesort(int sort[], int tmp[], int low, int high/*, int *cptr*/){   
	int mid = low + abs(high-low)/2; //mid是integer, 小數點自動捨去
	if(low < high){
		mergesort(sort,tmp,low,mid/*,cptr*/); 		//left half
		mergesort(sort,tmp,mid+1,high/*,cptr*/); 	//right half
		merge(sort,tmp,low,high/*,cptr*/);
	}
}
void edge_assign(int *edge_num_ptr, int node1, int node2, int weight){
	edge[*edge_num_ptr][0] = node1; 
	edge[*edge_num_ptr][1] = node2; 
	edge[*edge_num_ptr][2] = weight; 
}

void Prim(int node, int *edge_num_ptr){   
	int next;
	if(1 == A[node]){return;} //recursion end condition
	//find next node
	for(int i=0;i<MAX;i++){ 
		//find min weight edge
		if( -1 != T[node][i][0] && -1 != A[i]){   
			if( T[node][i][1] < edge[*edge_num_ptr][2] ){ //comparison of weight
				//swap if input node 1 > input node 2
				if(node < i){edge_assign(edge_num_ptr,node,i,T[node][i][1]);}
				else{edge_assign(edge_num_ptr,i,node,T[node][i][1]);}
				*edge_num_ptr += 1;
				next = i;
			}
		}
		else{break;}//end of array list
	}	
	A[next] = 1;			 		 //mark next point
	total_weight += T[node][next][1];//total weight = old w + new w
	Prim(next, edge_num_ptr);		 //go to next point
}

int main(){
	int in_edge_num = 0, edge_num = 0, opt_num = 0; //temp
	int *edge_num_ptr = &edge_num;
	int cnt = 0;
	int s = 0;

	scanf("%d",&set);
	printf("set = %d\n",set);
	//input data
	for(int i=0; i<set; i++){		
		printf("i = %d\n",i);
		//Initialization
		in_edge_num = edge_num = opt_num = total_weight = 0;		
		for(int i=0;i<MAX;i++){   
			edge[i][2] = INT_MAX;
			for(int j=0;j<MAX;j++){
				T[i][j][0] = -1;
				if(set > 0){T[i][j][1] = 0;}
			}
		}		
		//input data
		while(1){ //set 由換行鍵隔開，讀到換行鍵則停止輸入
			if( 2 == cnt)break;			
			//getchar();			
			s = scanf("%d %d %d\n",&nd1,&nd2,&w);			
			//fflush(stdin);
			// decide option
			if(0 == opt_num){
				opt_num = w;//option #
				printf("opt_num = %d\n",opt_num);
				continue;	//fisrt data, jump loop this time
			}

			printf("nd1=%d, nd2=%d, w=%d\n",nd1,nd2,w);
			//count edge
			in_edge_num++;
			if(s != 3){   //'\n' or EOF
				cnt += 1;
				printf("cnt = %d",cnt);
				if( 1 == cnt)break;
			}

			/*read = getline(&line, &len, stdin) -1; //-1 for stop counting newline character
			*(line+0) = nd1; 
			*(line+1) = nd2; 
			*(line+2) = w;*/
			
			//input to matrix (like linked list undirected version)
			for(int i=0;i<MAX;i++){   
				if(0 == T[nd1][i][1]){ 
					T[nd1][i][0] = nd2;					
					T[nd1][i][1] = w;
					break;
				}
			}
			for(int i=0;i<MAX;i++){   
				if(0 == T[nd2][i][1]){ 
					T[nd2][i][0] = nd1;					
					T[nd2][i][1] = w;
					break;
				}
			}
		}
		/*
		for(int k=0; k<in_edge_num; k++){
			for(int i=0; i<in_edge_num; i++){	
				for(int j=0; j<in_edge_num; j++){	
					printf("T[%d][%d][%d]= %d\n",i,j,k,T[i][j][k]);
				}
				printf("\n");
			}
			printf("\n\n");
		}
		*/
		//Prim algorithm, always start from zero
/*		A[0] = 1;
		Prim(0,&edge_num);
		//sorting edge array
		//mergesort(edge,tmp,0,*edge_num_ptr);
		//print result		
		if(1 == opt_num){   
			for(int i=0; i<*edge_num_ptr; i++){   
				printf("%d %d\n",tmp[i][0],tmp[i][1]);
			}
		}
		printf("%d\n",total_weight);*/
	}
	return 0;
}
