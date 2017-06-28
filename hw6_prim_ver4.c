#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX 1001
//#define DEBUG

#ifdef DEBUG
#define DBG(str, ...)                                                                    \
    do {                                                                                 \
        fprintf(stdout, str, ##__VA_ARGS__);                                             \
        fflush(stdout);                                                                  \
    } while (0)
#else
#define DBG(str, ...)                                                                    \
    {                                                                                    \
    }
#endif

typedef struct {
    int node[2];
    int weight;
} Edge;

int T[MAX][MAX] = {}, predecessor[MAX] = {}, key[MAX] = {}, visited[MAX] = {}, node[MAX] = {};
	//node[]:紀錄那些node有使用到
int column = 3, wc_num = 3, set = 0, opy_num = 0, nd1 = 0, nd2 = 0, w = 0, edge_num = 0,
    total_node = 0,	total_weight = 0; // column: merge sort column #, wc: weight column #

Edge edge_sort[MAX] = {}, edge[MAX] = {};

int compare_edge(const void *a, const void *b)//這函式是 qsort 所需的比較函式
{
	Edge x = *(Edge *)a;
	Edge y = *(Edge *)b;

	if( ( x.node[0] > y.node[0]) || ( (x.node[1] > y.node[1]) && (x.node[0] == y.node[0]) ) )
		return 1;
	else if( ( x.node[0] <  y.node[0]) || ( (x.node[1] < y.node[1]) && (x.node[0] == y.node[0]) ) )
		return -1;
	else
		return 0;
}

bool parse_line(char *line, int *ret_value)
{
    if (line == NULL || strlen(line) <= 1) return false;
    char *pch   = NULL;
    int   index = 0;

//    DBG("Splitting string: %s", line);
    pch = strtok(line, " ");
    while (pch != NULL) {
//        DBG("\t%s\n", pch);
        ret_value[index] = atoi(pch);
        pch              = strtok(NULL, " ");
        index++;
    }
    return true;
}

void reset_all_data(void)
{	
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            T[i][j] = 0;
        }
    }

    for (int i = 0; i < MAX; i++) {
        edge[i].node[0] = -1;
        edge[i].node[1] = -1;
        edge[i].weight = INT_MAX;

		predecessor[i] = -1;
		key[i] = INT_MAX;
    }

    memset(edge_sort, 0, sizeof(edge_sort));
    memset(visited, 0, sizeof(visited));
    memset(node, 0, sizeof(node));

	total_weight = 0;		
	total_node = 0;		
}

void Prim(int start_node, int node_num, int control_code)	
{
	key[start_node] = 0;
	DBG("\n---total_node = %d---\n",total_node);
	while( node_num  > 0){ // do V times			
		int weight_tmp = INT_MAX, mst_node = -1;
	    DBG("---cnt = %d ---\n",node_num);
		//choose min key[] value node into MST
		//for(int i=0; i<total_node; i++){   
		for(int i=0; i<MAX; i++){   
			if( weight_tmp > key[i] && 0 == visited[i] && 1 == node[i]){				
				weight_tmp = key[i];
				mst_node = i;
			}
		}
		
		//mark next_node
		DBG("key[%d] = %d, mst_node = %d\n",mst_node,weight_tmp,mst_node);
		visited[mst_node] = 1;
		
		//update vertex info connected to mst_node	
		//for(int i=0; i<total_node; i++){   			
		for(int i=0; i<MAX; i++){   
			//check who connected to mst_node 
			//for unvisited node[i]: if key[i] > weight(mst_node,i) update their predecessor and key
			if(T[mst_node][i] > 0 && key[i] > T[mst_node][i] && 1 != visited[i] && 1 == node[i] ){
				predecessor[i] = mst_node;  // update parent
				key[i] = T[mst_node][i];    // update key[i] = weight(nst_node,i)
			}
		}			
		node_num--;
/*	DBG("predecessor[]\n");		
	for(int i=0; i <2*total_node; i++){   
		DBG(" p[%d]: %d",i,predecessor[i]);
	}
	DBG("\n");
	DBG("key[]\n");		
	for(int i=0; i < 2*total_node; i++){   
		DBG(" k[%d]: %d",i,key[i]);
	}
	DBG("\n");
	DBG("visited[]\n");		
	for(int i=0; i < 2*total_node; i++){   
		DBG(" v[%d] : %d",i,visited[i]);
	}
	DBG("\n");*/	
	}
	
	//build MST tree
	//for(int i=0; i<total_node; i++){			
	for(int i=0; i<MAX; i++){   
		if(1 == visited[i] && -1 != predecessor[i] ){
			if(1 == control_code){
				if(predecessor[i] < i){
		   	    	edge[i].node[0] = predecessor[i];
	   				edge[i].node[1] = i;
				}
				else{   
	   		    	edge[i].node[0] = i;
	   				edge[i].node[1] = predecessor[i];
				}
			}
	        edge[i].weight = key[i];
			total_weight += key[i];
		}
	}	

	//if control_code = 1, sorting edge
	if(1 == control_code){		
		qsort((void *)edge, MAX, sizeof(Edge), compare_edge);	
	}
}

void Print_result(int control_code){   
	//input edge
	DBG("control code = %d\n",control_code);		
	DBG(" Print_result = %d\n",control_code);		
	
	//print mst edge
	if(1 == control_code ){ // print edge only when control_code = 1        
		for(int i= MAX - (total_node-1); i < MAX; i++){//need to be fixed, only has to output V-1 times
			DBG("i  = %d\t",i);
			DBG("weight of edge(%d, %d) = %d\t",edge[i].node[0],edge[i].node[1],edge[i].weight);
			printf("%d %d\n",edge[i].node[0],edge[i].node[1]);
		}
		DBG("\n");			
	}
	//print total weight	
	DBG("total_weight = %d\n",total_weight);
	printf("%d\n",total_weight);
}

int main()
{
    char line[1024] = {};
    int total_sets = 0;

    fgets(line, sizeof(line), stdin);
    total_sets = atoi(line);
    // Read data
    for (int current_set = 0; current_set < total_sets; current_set++) {
        int  value[3]   = {};
        int  index      = 0;

        DBG("--- Running Set %d, total_set = %d ---\n", current_set,total_sets);
        reset_all_data();

        // Read the control code
        line[0] = '\0'; // Empty the string
        fgets(line, sizeof(line), stdin);
        if (parse_line(line, value) == false) break;
        int control_code = value[2];
        DBG("Control #: %d\n", control_code);
        index++;
        while (1) {
//            DBG("--- Running Index %d ---\n", index);
            line[0] = '\0'; // Empty the string
            fgets(line, sizeof(line), stdin);
            // Exit when this line is invalid.
            if (parse_line(line, value) == false) break;
            // 接下來就可以自由使用value陣列，一切都會正常
            DBG("Inputs: %d %d %d\n", value[0], value[1], value[2]);
			//count which node is used
			node[value[0]] = 1;
			node[value[1]] = 1;
			//weight assignment
			if(	0 == T[value[0]][value[1]] ){ // if tmp_max > input edge weight, update tmp_max
				T[value[0]][value[1]] = value[2]; 
				T[value[1]][value[0]] = value[2]; 
			}
			else{   
				if( T[value[0]][value[1]] > value[2] ){ // same node to node set has other paths, update smaller path weight
					T[value[0]][value[1]] = value[2]; 
					T[value[1]][value[0]] = value[2]; 					
				}				
			}
            index++;
        }
		//count total # of node used
		for(int i=0; i<MAX; i++){ 
			if(0 != node[i]){
				DBG("node[%d] = %d\t",i,node[i]);
			}
			total_node += node[i];
		}
        // Do_MST(), Prim start from node 0
		Prim(0, total_node, control_code);
        Print_result(control_code);
    }
    return 0;
}
