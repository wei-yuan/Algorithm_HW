#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MAX 1000 

int T[MAX][MAX][2] = {}, edge_sort[MAX*3] = {}, edge[MAX*3] = {}, visited[MAX] = {}, column = 3, wc_num = 3, set =0, opy_num = 0, nd1 = 0, nd2 = 0, w = 0, total_weight = 0; //opt_num: option, column: merge sort column #, wc: weight column #

//read line
char *line = NULL;
size_t len = 0;	  //unsigned
ssize_t read = 0; //signed

//如何更簡潔？
void merge(int sort[], int tmp[], int low, int high){  //Divide and conquer
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

void getline_to_integer(int read, char *lineptr){	
	int integer[3] = {}, i_cnt = 0, var_cnt = 0, tmp = 0, sum = 0;
	for(int i=0; i<read; i++){
		tmp = *(lineptr+i) - '0';//only for positive integer
		// int ascii code of (space = 32, newline = 10, number 0 = 48) => space = -16, new line = -38
		if ( -38 == tmp || -16 == tmp ){			
			//combine single number(s) into get correct number
			if(1 == i_cnt){sum = integer[0];}
			else if(2 == i_cnt){sum = integer[0]*10 + integer[1];}
			else {sum = integer[0]*10*10 + integer[1]*10 + integer[2];}			
			//number assign to variable
			if(0 == var_cnt){nd1 = sum;}
			else if(1 == var_cnt){nd2 = sum;}
			else{w = sum;}
			var_cnt++;
			i_cnt = 0;					
		}	
		else{   		
			*(integer+i_cnt) = tmp;
			i_cnt++;		
		}
	}	
	printf("nd1 =%d, nd2 =%d, w =%d\n",nd1,nd2,w);
}
//是否必要?
void edge_assign(int *edge_num_ptr, int node1, int node2, int weight){
	edge[(*edge_num_ptr)*3 +0] = node1; 
	edge[(*edge_num_ptr)*3 +1] = node2; 
	edge[(*edge_num_ptr)*3 +2] = weight; 
}
void Prim(int node, int *edge_num_ptr){   
	int next;
	printf("---Prim---\n");
		
}

int main(){
	int in_edge_num = 0, edge_num = 0, opt_num = 0;
	int *edge_num_ptr = &edge_num; // for count edge number select into edge[]

	scanf("%d\n",&set);
	//Initialization
	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			T[i][j][0] = -1;
		}
	}

	//Read data
	while(1){			
		read = getline(&line, &len, stdin) /*-1*/; //-1 for stop counting newline character						
		//printf("----line length = %zd\n",read);		
		if( 1 == read || -1 == read ){ //end of set			
			/*Prim algorithm, always start from zero*/			
			visited[0] = 1;
			Prim(0,&edge_num);
			for(int i=0; i<*edge_num_ptr; i++){   
				printf("%d %d %d\n",edge[i*3+0],edge[i*3+1],edge[i*3+2]);
			}
			
			/*sorting edge array*/
/*			mergesort(edge,tmp,0,*edge_num_ptr);
			//print result
			if(1 == opt_num){   
				for(int i=0; i<*edge_num_ptr; i++){   
					//printf("%d %d\n",tmp[i+0],tmp[i+1]);
					printf("edge= %d,edge = %d\n",edge[i+0],edge[i+1]);
				}
			}
			printf("%d\n",total_weight);*/
			//end condition				
			if(-1 == read){break;}	
			/*Re-initialization*/
			in_edge_num = edge_num = opt_num = total_weight = 0;		
			for(int i=0;i<MAX;i++){   
				edge[i+2] = INT_MAX;
				for(int j=0;j<MAX;j++){
					T[i][j][0] = -1;
					if(set > 0){T[i][j][1] = 0;}
				}
			}
			printf("---- set ----\n");
			continue;
		}
		//from getline to correct number
	    getline_to_integer(read,line);
		in_edge_num++;
		if(1 == in_edge_num){   
			opt_num = w;
			printf("opt_num = %d\n",opt_num);
			continue;
		}
		//input T array
		for(int i=0;i<MAX;i++){   
			if(-1 == T[nd1][i][0]){   
				T[nd1][i][0] = nd2;
				T[nd1][i][1] = w;				
				printf("T[%d][%d][%d]= %d ",nd1,i,0,T[nd1][i][0]);
				printf("T[%d][%d][%d]= weight = %d\n",nd1,i,1,T[nd1][i][1]);
				break;				
			}			
		}
		for(int i=0;i<MAX;i++){   
			if(-1 == T[nd2][i][0]){   
				T[nd2][i][0] = nd1;
				T[nd2][i][1] = w;
				printf("T[%d][%d][%d]= %d ",nd2,i,0,T[nd2][i][0]);
				printf("T[%d][%d][%d]= weight = %d\n",nd2,i,1,T[nd2][i][1]);
				break;				
			}
		}
	}//while

	free(line);
	return 0;
}
			//test input
			/*for(int k=0; k<1; k++){
				for(int i=0; i<in_edge_num; i++){
					for(int j=0; j<in_edge_num; j++){
						printf("T[%d][%d][%d]= %d ",i,j,k,T[i][j][k]);
					}
					printf("\n");
				}
				printf("\n");
			}*/

