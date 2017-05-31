#include <stdio.h>
#define max 1000

int T[max][max] = {}, visited[max] = {}, parent[max] = {}, start[max] = {}, finish[max] = {}, set = 0, node = 0, edge = 0, p = 0, c = 0, timer = 0, no = 0;//T[row][column] //p:parent, c:child  
void G(int parent, int child){   
	*(*(T+parent)+child) = 1; //point to parent node
}
void DFS(int i, int *tptr){  
//	printf("-------------------\n");
//	printf("node %d, start time = %d\n",i,*tptr);
	for(int j=0; j<node; j++){   		
		if( !visited[j] && *(*(T+i)+j) == 1){ // !visited[] -> check false or not
			*(visited+j) = 1;//node j already visited						
			*tptr += 1;
			*(start+j) = *tptr;
			DFS(j,tptr);
		}	
	}	
	*tptr += 1;
	*(finish+i) = *tptr;
//	*(finish+i) = *(tptr)+1;//wrong, do not change timer
//	printf("node %d, end time = %d\n",i,*(finish+i));
}

void edge_cls(int i){
	for(int j=0; j<node; j++){   
		if( *(*(T+i)+j) == 1){ // !visited[] -> check false or not
			if( *(visited+i) == 2 && *(visited+j) == 2)return; //<u,v> are both black node, stop this branch
			
			if( *(visited+j) == 0){//v = white node		
				*(visited+j) = 1;//change node j to gray
				//printf("tree edge <%d,%d>\n",i,j);
				edge_cls(j);								
			}
			else if( *(visited+j) == 1 ){ //v = gray node, back edge, do nothing 
				/*if((start[j] < start[i]) && (start[i] < finish[i]) && (finish[i] < finish[j]))
					printf("back edge <%d,%d>\n",i,j);*/
			}				
			else{ // v =  black node
				/*if( (start[i] < start[j]) && (start[j] < finish[j]) && (finish[j] < finish[i]) )
					printf("forward edge <%d,%d>\n",i,j);
				else
					printf("cross edge <%d,%d>\n",i,j);*/
				no = 1;
				return;	
			}
		}		
	}
	visited[i] = 2;//change node j to black
}

int main(){   
	int *tptr = &timer;	

	scanf("%d",&set);
	for(int i=0; i<set; i++){
		//printf("---- set = %d ----\n",i+1);
		scanf("%d",&node);
		scanf("%d",&edge);
	
		for(int i=0; i<edge; i++){
			scanf("%d %d",&p,&c); 
			*(parent+c) = p;
			G(p,c);
		}

		//directed graph DFS, make tree
		for(int i=0; i<node; i++){
			if(!visited[i]){
				*(visited+i) = 1;				
				*(start+i) = *tptr;
				DFS(i,&timer);
			}
		}
		//zero
		for(int i=0; i<node; i++){visited[i] = 0;}

		//edge classififcation
		for(int i=0; i<node; i++){
			if(!visited[i]){			
				*(visited+i) = 1;				
				edge_cls(i);
			}
		}
				
		//check
/*		for(int i=0; i<node;i++){   
			printf("node %d, start[%d] = %d, finish[%d] = %d\n",i,i,start[i],i,finish[i]);
		}		
*/
		//optput result
		if(no == 1){printf("%d NO\n",i+1);}
		else{printf("%d YES\n",i+1);}

		//find forward edge & cross edge
		if(set-1 == i)break;
		//zero		
		*tptr = no = 0;
		for(int i=0; i<node; i++){   
			visited[i] = 0;
			for(int j=0; j<node; j++){*(*(T+i)+j) = 0;}
		}
	}//for loop
	return 0;
}
