#include <stdio.h>
#define column 1000
int T[column+1]= {};
void M(int node){   
	*(T+node) = node; //T[rows][columns] = link to itself
}
void G(int child, int parent){   
	*(T+child) = parent; //point to parent node
}
int F(int node, int dptr){
	if( *(T+node) == node )
		return dptr;
	return	F(*(T+node),dptr+1);
}
int main(){
	int nd1,nd2,dptr = 0;
	char op; //op -> opcode

	while(1){   
		nd1 = nd2 = 0;		
		scanf("%c",&op);
		if(op == 'M'){
			scanf("%d",&nd1);
			M(nd1);
		}
		else if(op == 'G'){   
			scanf("%d %d",&nd1,&nd2);
			G(nd1,nd2);									
		}
		else if( op == 'F'){   
			scanf("%d",&nd1);
			dptr = F(nd1,0);
			printf("%d %d\n",nd1,dptr);
		}
		else if( op == 'E')break;				
	}
	return 0;
}
