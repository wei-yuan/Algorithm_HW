#include <stdio.h>
#define max 1000

int G[max][max] = {}, visited[max] = {},  start[max] = {}, finish[max] = {}, set = 0, node = 0, edge = 0, p = 0, c = 0, timer = 0, no = 0, scnt = 0, back = 0;//T[row][column] //p:parent, c:child  
int st_v[max] = {}; //subtree_visisted[]

void Graft(int parent, int child){   
	*(*(G+parent)+child) = 1; //point to parent node
}
void DFS(int i, int *tptr){  
	for(int j=0; j<node; j++){   		
		if( visited[j] == 0 && *(*(G+i)+j) == 1){ // !visited[] -> check false or not
			*(visited+j) = 1;//node j already visited						
			*tptr += 1;
			*(start+j) = *tptr;
			DFS(j,tptr);			
		}
		if( *(visited+i) == 2 && *(visited+j) == 2)return; //<u,v> are both black node, stop this branch		
	}	
	*tptr += 1;
	*(finish+i) = *tptr;
}

void edge_cls(int i, int *sptr, int *bptr){
	for(int j=0; j<node; j++){   
		if( *(*(G+i)+j) == 1){ // !visited[] -> check false or not
			if( *(visited+i) == 2 && *(visited+j) == 2)return; //<u,v> are both black node, stop this branch			
			if( *(visited+j) == 0){//v = white node		
				*(visited+j) = 1;  //change node j to gray
				*(st_v+j) = *sptr; //count which branch
				printf("tree edge <%d,%d>\n",i,j);
				edge_cls(j, sptr, bptr);								
			}
			else if( *(visited+j) == 1 ){ //v = gray node, back edge, do nothing 
				//if((start[j] < start[i]) && (start[i] < finish[i]) && (finish[i] < finish[j]))
					printf("back edge <%d,%d>\n",i,j);
					if( *(st_v+j) < *(st_v+i)){ 
						*bptr += 1;
						if(*bptr > 1){ 
							no = 1;
							return;
						}
					}
			}				
			else{ // v =  black node
/*				if( (start[i] < start[j]) && (start[j] < finish[j]) && (finish[j] < finish[i]) ){
					printf("forward edge <%d,%d>\n",i,j);
					no = 1;
					return;					
				}					
				//else{
				else if( (start[j] < finish[j]) && (finish[j] < start[i]) && (start[i] < finish[i]) ){
					printf("cross edge <%d,%d>\n",i,j);
					no = 1;
					return;	
				}*/
					no = 1;
					return;					
			}
			*sptr += 1;
		}		
	}
	*(visited+i) = 2;//change node j to black
}

int main(){   
	int *tptr = &timer;	
	int *sptr = &scnt;
	int *bptr = &back;

	scanf("%d",&set);
	for(int i=0; i<set; i++){
		//printf("---- set = %d ----\n",i+1);
		scanf("%d",&node);
		scanf("%d",&edge);
	
		for(int i=0; i<edge; i++){
			scanf("%d %d",&p,&c); 
			Graft(p,c);
		}

		//directed graph DFS, make tree
		for(int i=0; i<node; i++){
			if(visited[i] == 0){
				*(visited+i) = *(st_v+i) = 1;				
				*(start+i) = *tptr;
				DFS(i,&timer);				
			}
		}
		//zero
		for(int i=0; i<node; i++){*(visited+i) = 0;}

		//edge classififcation
		for(int i=0; i<node; i++){
			if(visited[i] == 0){			
				*(visited+i) = 1;				
				edge_cls(i, &scnt, &back);
			}
			if( 1 == no){break;}			
		}
				
		//check
		for(int i=0; i<node;i++){   
			printf("node %d, start[%d] = %d, finish[%d] = %d, visited[%d] = %d, st_v[%d] = %d\n",i,i,start[i],i,finish[i],i,visited[i],i,st_v[i]);
		}		

		//optput result
		if(1 == no){printf("%d NO\n",i+1);}
		else{printf("%d YES\n",i+1);}

		//find forward edge & cross edge
		if(set-1 == i)break;
		//zero		
		*tptr = no = back = 0;
		for(int i=0; i<node; i++){   
			*(visited+i) = *(st_v+i) = 0;
			for(int j=0; j<node; j++){*(*(G+i)+j) = 0;}
		}
	}//for loop
	return 0;
}
