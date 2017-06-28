#include <stdio.h>
#include <stdlib.h>


#define MAX 1001

int Array[MAX] = {};

typedef struct list_node {
	int data;
	struct list_node *next;
}node;	

void M(int i){   
	node node_i;
	//Array[i] = 
}

void G(int r,int v){  //Graft r & v, r -> v
	
}

int main(){
	int nd1,nd2;
	char op; //op -> opcode

	for(int i=0;i<5;i++){   
		node i = {.data = 0};
		printf("node %d = %d",node i->data);
	}
	
/*	for(int i=0;i<5;i++){   
		printf("node %d = %d",i->data);
	}
	while(1){   
		scanf("%c",&op);
		if(op == 'M'){ 
			scanf("%d",&nd1);
//			printf("Input is %c %d\n",op,nd1);
//			M(nd1);
		}	
		else if(op == 'G'){   
			scanf("%d %d",&nd1,&nd2);
//			printf("Input is %c %d %d\n",op,nd1,nd2);
			G(nd1,nd2);									
		}
		else if( op == 'F'){   
			scanf("%d",&nd1);
//			printf("Input is %c %d\n",op,nd1);
//			printList(nd1);
		}
		else if( op == 'E')break;		
		nd1 = nd2 = 0;
		//		free(n);
	}*/
	return 0;
}
