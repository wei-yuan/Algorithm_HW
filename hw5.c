#include <stdio.h>
#define max 1000

int G[max][max] = {}, visited[max] = {}, start[max] = {}, finish[max] = {}, nv[max] = {}, set = 0, node = 0, edge = 0, p = 0, c = 0, no = 0;//G[row][column]// T: transpose of G //p:parent, c:child  
void Graft(int array[][max], int parent, int child){   
	*(*(array+parent)+child) += 1; //point to parent node
	if( *(*(array+parent)+child) >= 2){no = 1;}
}
void DFS(int array[][max], int i){  	
	for(int j=0; j<node; j++){   		
		if( 1 == *(*(array+i)+j) ){ // !visited[] -> check false or not
			/*----break condition 1----*/
			if( 2 == *(visited+i) && 2 == *(visited+j))break; //<u,v> are both black node, stop this branch			
			/*----depth first search----*/
			if( 0 == *(visited+j)){//v = white node		
				*(visited+j) = 1;//node j already visited
				*(nv+j) += 1;				
				DFS(array,j);							
			}
			else if( 2 == *(visited+j) ){ //v = gray node, back edge, do nothing 
				*(nv+j) += 1;				
			}				
		}				
	}
	*(visited+i) = 2;//change node j to black	
}

int main(){   
	scanf("%d",&set);
	for(int i=0; i<set; i++){
		scanf("%d",&node);
		scanf("%d",&edge);
		for(int i=0; i<edge; i++){
			scanf("%d %d",&p,&c); 
			Graft(G,p,c);			
		}
		//directed graph DFS
		for(int i=0; i<node; i++){
			if( 1 == no ){break;}
			if( 0 == *(visited+i) ){
				*(visited+i) = 1;				
				*(nv+i) += 1;				
				DFS(G,i);				
			}
			//check singly or not
			for(int i=0; i<node; i++){   
				if( 2 <= *(nv+i) ){ 
					no = 1;
					break;
				}
			}			
			//clear
			for(int i=0; i<node; i++){*(visited+i) = *(nv+i)= 0;}			
		}
		//optput result
		if(1 == no){printf("%d NO\n",i+1);}
		else{printf("%d YES\n",i+1);}

		if(set-1 == i){break;}
		//zero		
		no = 0;
		for(int i=0; i<node; i++){   
			for(int j=0; j<node; j++){*(*(G+i)+j) = 0;}
		}
	}//for loop
	return 0;
}
