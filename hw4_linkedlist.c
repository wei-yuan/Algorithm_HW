#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

struct node {
   	int data;
	struct node *next;
};
struct node *head = NULL; //intitialization list head
/*
void M(int value){ //make tree: creat node
    struct node *n = (struct node *)malloc(sizeof(struct node)); // 動態配置記憶體
    n->data = value;
    n->next = n;     //point to itself
}
*/
void G(int r,int v){  //Graft r & v
	// r -> v
	struct node *list = (struct node *)malloc(sizeof(struct node)); 
	struct node *lnxt = (struct node *)malloc(sizeof(struct node)); // list next
		
	if( head == NULL ){      //
//		printf("---head = NULL---\n");
		head = list; 	   //make head node != NULL -> 是否必要？
		head->data = v;						
		head->next = head; //head node point back to itself
//		printf("create new head\nhead data = %d\n",head->data);
//		printf("---head data = %d, list data = %d--- \n",head->data,lnxt->data);
		lnxt->data = r;
		lnxt->next = head; //list node point to head		
//		printf("---head data = %d, list data = %d--- \n",head->data,lnxt->data);
	}
	else{   
//		printf("---head =/= NULL---\n");
		list->data = v;				
		if( v != head->data ){ 	//new root != old list last term
			list->next = list;  //new root point to itself
//			printf("new root, list->next = list itself\n");			
		}
		else{
			list->next = head;	//list point to old head temp						
//			printf("connect to old head\n");			
		}				
		lnxt->data = r;	
		lnxt->next = list;
		head = lnxt;        //lnxt:r be new head			
	}
}
//待修改
/*
int find_node(int value){   
	printf("---search---\n");
	struct node *q;      //a pointer point to struct type
//	q = head->next; // only information u know?
	while(sptr != NULL && sptr->data != value){
		sptr = sptr->next;
		printf("node data = %d",sptr->data);
	}		
	return sptr;	
}
*/
//待修改
int search(int value){   
	struct node *sptr = head;      //a pointer point to struct type
//	q = head->next; // only information u know?
	while(sptr != NULL && sptr->data != value){
		sptr = sptr->next;
		printf("node data = %d",sptr->data);
	}		
	return sptr;	
}
void printList(int value){
	int depth = 0;
//	struct node *ptr = head;
	struct node *ptr;	
	ptr = search(value); //assign ptr = sptr
//	printf("\n[");
	if(ptr != NULL){		
		while( ptr->next != ptr ){   
			printf(" list= %d , depth =%d ",ptr->data,depth); 
			ptr = ptr->next;
			depth++;
		}
	}
	else printf(" head = NULL ");
//	printf("]\n");
	printf("final depth =%d\n",depth);
}

int main(){
	int nd1,nd2;
	char op; //op -> opcode

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
			printList(nd1);
		}
		else if( op == 'E')break;		
		else
		nd1 = 0;
		nd2 = 0;
//		free(n);
	}
	return 0;
}
