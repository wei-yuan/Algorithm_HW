#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX 10000
//#define DEBUG

#ifdef DEBUG
#define DBG(str, ...)                        \
	do                                       \
	{                                        \
		fprintf(stdout, str, ##__VA_ARGS__); \
		fflush(stdout);                      \
	} while (0)
#else
#define DBG(str, ...) \
	{                 \
	}
#endif

typedef struct
{
	int node[2];
	int weight;
} Edge;

int subset[MAX] = {}, node[MAX] = {}; //node[]:紀錄那些node有使用到

int column = 3, wc_num = 3, set = 0, edge_num = 0,
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
	if (line == NULL || strlen(line) <= 1)
		return false;
	char *pch = NULL;
	int index = 0;

	//DBG("Splitting string: %s", line);
	pch = strtok(line, " ");
	while (pch != NULL)
	{
		//DBG("\t%s\n", pch);
		ret_value[index] = atoi(pch);
		pch = strtok(NULL, " ");
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
}

//find root of node i
int FindSetCollapsing(int *subset, int i)
{ 
	DBG("input node  = %d\n", i); 
	int root;
	for (root = i; subset[root] >= 0; root = subset[root]); //若非disjoint set, 更新變數root 為 input node的root node

	/*更新輸入節點i的root為每次最新的root*/
	while (i != root) //檢查input node 是否為root; 若否,則更新input node為其parent node
	{
		DBG("i != root\n");
		int parent = subset[i];
		subset[i] = root;
		i = parent;
		DBG("\tsubset[%d] = %d", i, subset[i]);
	}
	DBG("\tFindSet root  = %d\n", root);
	return root;
}

void UnionSet(int *subset, int xroot, int yroot)
{ //update subset of a node

	// 用rank比較, 負越多表示set越多element, 所以是值比較小的element比較多
	// xroot, yroot的subset[]一定都是負值吸收
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
}

void Kruskal(int edge_num, int control_code)
{
	//DBG("\n---total_node = %d---\n", total_node);
	// sorting edge by weight
	qsort((void *)edge, MAX, sizeof(Edge), compare_edge);

	//DBG("-- edge number = %d ---\n", edge_num);
	int sort_edge_num = 0, node1root = 0, node2root = 0;

	//選擇權重最小的edge到MST中(edge_sort)
	for (int i = 0; i < edge_num; i++)
	{
		//選之前判斷兩個node是否在同個set
		node1root = FindSetCollapsing(subset, edge[i].node[0]); //find node1 root
		node2root = FindSetCollapsing(subset, edge[i].node[1]); //find node2 root

		if ((sort_edge_num == 0 && node1root == node2root) || node1root != node2root)//不同set, 選入
		{
			if (sort_edge_num == 0)
			{
				DBG("First edge\n");
			}
			//choose edge
			edge_sort[sort_edge_num].node[0] = edge[i].node[0];
			edge_sort[sort_edge_num].node[1] = edge[i].node[1];
			edge_sort[sort_edge_num].weight = edge[i].weight;
			DBG("\tedge_sort[%d].node[0] = %d, node1root = %d, edge_sort[%d].node[1] = %d, node2root = %d\n", sort_edge_num, edge_sort[sort_edge_num].node[0], node1root, sort_edge_num, edge_sort[sort_edge_num].node[1], node2root);
			//Union two nodes into set
			UnionSet(subset, node1root, node2root);

			sort_edge_num++;
		}
		else //同個set, 不選
		{ 
		}
	}

	DBG("subset[]\n");
	for (int i = 0; i < total_node; i++)
	{
		DBG(" subset[%d]: %d", i, subset[i]);
	}
	DBG("\n");

	for (int i = 0; i < sort_edge_num; i++)
	{
		total_weight += edge_sort[i].weight;
	}
}

void Print_result(int control_code)
{
	//print mst edge
	if (1 == control_code)
	{ // print edge only when control_code = 1
		for (int i = 0; i < total_node - 1; i++)
		{ //need to be fixed, only has to output V-1 times
			if (0 == edge_sort[i].node[0] && 0 == edge_sort[i].node[1])
			{
				break;
			}
			DBG("weight of edge(%d, %d) = %d\t", edge_sort[i].node[0], edge_sort[i].node[1], edge_sort[i].weight);
			DBG("i  = %d\t", i);
			printf("%d %d\n", edge_sort[i].node[0], edge_sort[i].node[1]);
		}
		DBG("\n");
	}
	//print total weight
	DBG("total_weight = %d\n", total_weight);
	printf("%d\n", total_weight);
}

int main()
{
	char line[1024] = {};
	int total_sets = 0;

	fgets(line, sizeof(line), stdin);
	total_sets = atoi(line);

	// Read data
	for (int current_set = 0; current_set < total_sets; current_set++)
	{
		int value[3] = {};
		int index = 0;
		int edge_num = 0;

		DBG("--- Running Set %d, total_set = %d ---\n", current_set, total_sets);
		reset_all_data();

		// Read the control code
		line[0] = '\0'; // Empty the string
		fgets(line, sizeof(line), stdin);
		if (parse_line(line, value) == false)
			break;
		int control_code = value[2];
		DBG("Control #: %d\n", control_code);
		index++;
		while (1)
		{
			DBG("--- Running Index %d ---\n", index);
			line[0] = '\0'; // Empty the string
			fgets(line, sizeof(line), stdin);
			// Exit when this line is invalid.
			if (parse_line(line, value) == false)
				break;
			// 接下來就可以自由使用value陣列，一切都會正常
			DBG("Inputs: %d %d %d\n", value[0], value[1], value[2]);
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

		for (int i = 0; i < MAX; i++)
		{
			if (0 != node[i])
			{
				DBG("node[%d] = %d\t", i, node[i]);
			}
			total_node += node[i];
		}
		// Do_MST(), Prim start from node 0
		DBG("\n");
		Kruskal(edge_num, control_code);
		Print_result(control_code);
	}
	return 0;
}