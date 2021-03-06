#include <stdio.h>
#define max 1000

int G[max][max] = {}, T[max][max] = {}, visited[max] = {}, bstack[max][2] ={}, bv[max] = {}, set = 0, node = 0, edge = 0, p = 0, c = 0,  no = 0, num_back = 0, end = 0;//G[row][column]// T: transpose of G //p:parent, c:child  

void Graft(int array[][max], int parent, int child){   
	*(*(array+parent)+child) = 1; //point to parent node
}

void DFS(int array[][max], int i, int ori_parent, int *sptr, int *eptr){  	
	//when array == T & traverse reach to end node ori_parent, stop DFS
	if(1 == *eptr)return;
	for(int j=0; j<node; j++){   		
		/*----break condition 1----*/		
		//if(1 == *eptr)break;

		if( 1 == *(*(array+i)+j) ){ // !visited[] -> check false or not
			/*----break condition 2----*/
			if( *(visited+i) == 2 && *(visited+j) == 2)return; //<u,v> are both black node, stop this branch			
			if( G == array && i == j){				
				/*printf("G[%d][%d] = %d\n",i,j,array[i][j]);
				printf("point to itself, node %d = node %d\n",i,j);*/
				continue;
			}			
			if( T == array && ori_parent == j){   
				/*printf("--- end of T array ---\n");
				printf("end node %d\n",i);
				printf("node i =%d, node j = %d, visited[%d] = %d, bv[%d] =%d\n",i,j,i,visited[i],i,bv[i]);*/
				*(bv+j) += 1;
				*(visited+j) = 2;//change node j to black				
				*eptr = 1;
				break;				
			}
			
			/*----depth first search----*/
			if( *(visited+j) == 0){//v = white node		
				printf("tree edge <%d,%d>\n",i,j);
				*(visited+j) = 1;//node j already visited
				if( T == array){ 					
					*(bv+j) += 1;					
					/*printf("--- T array ---\n");										 
					printf("node i =%d, node j = %d, visited[%d] = %d, bv[%d] =%d\n",i,j,i,visited[i],i,bv[i]);*/
				}
				DFS(array,j,ori_parent,sptr,eptr);							
			}
			else if( *(visited+j) == 1 ){ //v = gray node, back edge, do nothing 
				printf("back edge <%d,%d>\n",i,j);
				if( G == array){
					bstack[*sptr][0] = i;
					bstack[*sptr][1] = j;
					*sptr += 1;
				}
			}				
			else{ // v =  black node
				printf("forward or cross edge <%d,%d>\n",i,j);
				no = 1;
				return;
			}
		}				
	}
	*(visited+i) = 2;//change node j to black	
}

int main(){   
	int cnt = 0;	
	int *sptr = &num_back;//number of back edge
	int *eptr = &end;
	
	scanf("%d",&set);
	for(int i=0; i<set; i++){
		//printf("---- set = %d ----\n",i+1);
		scanf("%d",&node);
		scanf("%d",&edge);
	
		for(int i=0; i<edge; i++){
			scanf("%d %d",&p,&c); 
			Graft(G,p,c);
			Graft(T,c,p); //transpose of G		
		}
		
		//test
/*		for(int i=0; i<node;i++){   
			for(int j=0; j<node;j++){
				printf("G[%d][%d] = %d ",i,j,G[i][j]);				
			}
			printf("\n");
		}*/

		//directed graph DFS, make tree
		//printf("----G----\n");
		for(int i=0; i<node; i++){
			if( 1 == no){break;}
			if(visited[i] == 0){
				*(visited+i) = 1;				
				DFS(G, i, bstack[i][0], &num_back, &end);				
			}
		}
		
/*		for(int i=0; i<num_back;i++){   
			for(int j=0; j<2;j++)
				printf("bstack[%d][%d] = %d ",i,j,bstack[i][j]);
			printf("\n");
		}*/

		/*printf("----T----\n");
		printf("*num_back = %d\n", *sptr);*/
		//traverse all back edge
	if(*sptr > 1){
		for(int i=0; i<*sptr; i++){
			//clean for next traverse
			for(int i=0; i<node; i++){*(visited+i) = 0;}
			
			if( *(visited+ bstack[i][0]) == 0  ){						
				//printf("node %d\n",bstack[i][0]);
				*(visited+ bstack[i][0]) = 1;		
				*(bv+ bstack[i][0]) += 1;
				if(*eptr != 1){
					DFS(T, bstack[i][0], bstack[i][1], &num_back, &end);
				}
			}
			*eptr = 0; //zero for next round
			//check
			for(int i=0; i<node;i++){   
				printf("node %d, visited[%d] = %d, bv[%d] = %d\n",i,i,visited[i],i,bv[i]);
			}
		}

			for(int i=0; i<node; i++){
				if( cnt >= 2){   
					no = 1;
					break;
				}
				if( *(bv+i) >= 2){ cnt += 1;}
			}
	}//*sptr > 0

		//optput result
		if(1 == no){printf("%d NO\n",i+1);}
		else{printf("%d YES\n",i+1);}

		//find forward edge & cross edge
		if(set-1 == i)break;
		//zero		
		no = num_back = cnt = end = 0;
		for(int i=0; i<node; i++){   
			*(visited+i) = *(bv+i)= 0;
			for(int j=0; j<node; j++){*(*(G+i)+j) = *(*(T+i)+j)= 0;}
		}
	}//for loop
	return 0;
}
