#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX 10000

typedef struct
{
	int node[2];
	int weight;
} Edge;

int subset[MAX] = {}, node[MAX] = {};
//node[]:紀錄那些node有使用到
int column = 3, wc_num = 3, set = 0, nd1 = 0, nd2 = 0, w = 0, edge_num = 0,
	total_node = 0, total_weight = 0; // column: merge sort column #, wc: weight column #

Edge edge_sort[MAX] = {}, edge[MAX] = {};

int compare_edge(const void *a, const void *b) //這函式是 qsort 所需的比較函式
{
	Edge x = *(Edge *)a;
	Edge y = *(Edge *)b;

	return x.weight - y.weight;
}

bool parse_line(char *line, int *ret_value)
{
    if (line == NULL || strlen(line) <= 1) return false;
    char *pch   = NULL;
    int   index = 0;

    pch = strtok(line, " ");
    while (pch != NULL) {
        ret_value[index] = atoi(pch);
        pch              = strtok(NULL, " ");
        index++;
    }
    return true;
}

void reset_all_data(void)
{
	for (int i = 0; i < MAX; i++)
	{
		edge[i].node[0] = -1;
		edge[i].node[1] = -1;
		edge[i].weight = INT_MAX;

		subset[i] = -1;
	}

	memset(edge_sort, 0, sizeof(edge_sort));
	memset(node, 0, sizeof(node));

	total_weight = 0;
	total_node = 0;
	return;
}

int FindSetCollapsing(int *subset, int i)
{ //find root of node i

	int root; // root
	for (root = i; subset[root] >= 0; root = subset[root]);

	while (i != root)
	{
		int parent = subset[i];
		subset[i] = root;
		i = parent;
	}
	return root;
}

void UnionSet(int *subset, int x, int y)
{ //update subset of a node

	int xroot = FindSetCollapsing(subset, x),
		yroot = FindSetCollapsing(subset, y);

	// 用rank比較, 負越多表示set越多element, 所以是值比較小的element比較多
	// xroot, yroot的subset[]一定都是負值
	if (subset[xroot] <= subset[yroot])
	{ // x比較多element或是一樣多的時候, 以x作為root
		subset[xroot] += subset[yroot];
		subset[yroot] = xroot;
	}
	else
	{ //  if (subset[xroot] > subset[yroot]), 表示y比較多element
		subset[yroot] += subset[xroot];
		subset[xroot] = yroot;
	}
	return;
}

void Kruskal(int edge_num, int control_code)
{
	// sorting edge by weight
	qsort((void *)edge, MAX, sizeof(Edge), compare_edge);

	int sort_edge_num = 0, node1root = 0, node2root = 0;

	//選擇權重最小的edge到MST中(edge_sort)
	for (int i = 0; i < edge_num; i++)
	{
		//選之前判斷兩個node是否在同個set
		node1root = FindSetCollapsing(subset, edge[i].node[0]); //find node1 root
		node2root = FindSetCollapsing(subset, edge[i].node[1]); //find node2 root

		if ((sort_edge_num == 0 && node1root == node2root) || node1root != node2root)
		{
			//choose edge
			edge_sort[sort_edge_num].node[0] = edge[i].node[0];
			edge_sort[sort_edge_num].node[1] = edge[i].node[1];
			edge_sort[sort_edge_num].weight = edge[i].weight;

			//Union two nodes into set
			UnionSet(subset, edge_sort[sort_edge_num].node[0], edge_sort[sort_edge_num].node[1]);

			sort_edge_num++;
		}
		else
		{ //同個set, 不選
		}
	}

	for (int i = 0; i < sort_edge_num; i++)
	{
		total_weight += edge_sort[i].weight;
	}
	return;
}

void Print_result(int control_code)
{
	//print mst edge
	if (1 == control_code)
	{ // print edge only when control_code = 1
		for (int i = 0; i < total_node - 1; i++)
		{ //need to be fixed, only has to output V-1 times
			if ( 0 == edge_sort[i].node[0] && 0 == edge_sort[i].node[1] ){break;} 
			printf("%d %d\n", edge_sort[i].node[0], edge_sort[i].node[1]);
		}
	}
	//print total weight
	printf("%d\n", total_weight);
	return;
}

int main()
{
	//printf("55555555555555555\n");
	char line[1024] = {};
	int total_sets = 0;	
    
	fgets(line, sizeof(line), stdin);
	total_sets = atoi(line);
	// Read data	
	for (int current_set = 0; current_set < total_sets; current_set++)
	{
		//printf("66666666666666666666\n");
		int value[3] = {};
		int index = 0, edge_num = 0;

		reset_all_data();

		// Read the control code
		line[0] = '\0'; // Empty the string
		fgets(line, sizeof(line), stdin);
		if (parse_line(line, value) == false)
			break;
		int control_code = value[2];
		index++;
		while (1)
		{			
			line[0] = '\0'; // Empty the string
			fgets(line, sizeof(line), stdin);
			// Exit when this line is invalid.
			if (parse_line(line, value) == false) break;
			//count which node is used
			node[value[0]] = 1;
			node[value[1]] = 1;
			//edge information assignment
			if (value[0] > value[1])
			{ //make sure value[0] < value[1]
				edge[edge_num].node[1] = value[0];
				edge[edge_num].node[0] = value[1];
			}
			else
			{
				edge[edge_num].node[0] = value[0];
				edge[edge_num].node[1] = value[1];
			}
			edge[edge_num].weight = value[2];
			edge_num++;

			index++;
		}
		//count total # of node used
		for (int i = 0; i < MAX; i++)
		{
			total_node += node[i];
		}
		// Do_MST(), Prim start from node 0		
		Kruskal(edge_num, control_code);
		Print_result(control_code);		
	}	
	return 0;
}