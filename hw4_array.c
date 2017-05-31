#include <stdio.h>
//#include <stdlib.h>

int T[1000][1000] = {0};
void M(int node){   
	T[node-1][node-1] = 1; //T[rows][columns] = link to itself
}

void G(int child, int parent){   
	T[child-1][child-1] = 0;  //child node no longer point to itself
	T[child-1][parent-1] = 1; //and point to parent node
//	printf("T[%d][%d] = %d\n",child-1,parent-1,*(*(T+(child-1))+(parent-1)) );
}
void F(int node, int *dptr){   
	int column = sizeof(T[0])/4; // column number = size of first row, int alloc 4 byte on my computer
//	int column = 1000; //backup 
	if( T[node-1][node-1] != 1 ){   //if node is not root, keep search
		for(int j= 0;j<column;j++){   
			if( T[node-1][j] == 1){
//				printf("T[%d][%d] =%d, depth =%d\n",node-1,j,*(*(T+(node-1))+j),*dptr);
				*dptr += 1;
				F(j+1,dptr);
			}
		}
	}
	else return;//printf("node %d, depth = %d\n",node,cnt); // if T[node-1][node-1] = 1, no child, depth = 0
}

int main(){
	int nd1,nd2,cnt=0,depth = 0;
	int *dptr = &depth;
	char op; //op -> opcode

	while(1){   
		scanf("%c",&op);
		if(op == 'M'){
			scanf("%d",&nd1);
			M(nd1);
//			cnt++;			
		}
		else if(op == 'G'){   
			scanf("%d %d",&nd1,&nd2);
			G(nd1,nd2);									
		}
		else if( op == 'F'){   
			scanf("%d",&nd1);
			F(nd1,&depth);
			printf("%d %d\n",nd1,*dptr);
			*dptr = 0;
		}
		else if( op == 'E')break;				
		nd1 = 0;
		nd2 = 0;
	}
/*	for(int i =0;i<cnt;i++){
		for(int j=0;j<cnt;j++)
			printf("T[%d][%d]= %d ",i,j,*(*(T+i)+j) );
		printf("\n");
	}*/
	return 0;
}
