#include <cstdio>
#include <cstdlib>

#define Graph_is_directed 1
#define Graph_is_undirected 0

//采用邻接表的方式存储图结构
//定义边结构体 
typedef struct edge{
	int nextVertex;
	struct edge *next;
}edge;

//定义顶点结构体 
typedef struct vertex{
	int vertex;
	struct edge *first;
}vertex;


/*
	findCircleOfDirectedGraph的函数定义，主逻辑模块 
*/

//该函数是main里面调用的函数，是所有过程的综合 
void findCircleOfDirectedGraph();

//该函数用于判断图graph是否存在回路 
bool isCircleExistedInDirectedGraph(vertex **graph, int vertex);

//该函数用于查找到回路时，将被查找到的回路打印出来 
void printOneCircleOfDirectedGraph();


/*
	findCircleOfUndirectedGraph的函数定义，主逻辑模块 
*/

//该函数是main里面调用的函数，是所有过程的综合 
void findCircleOfUndirectedGraph();

//该函数用于判断图graph是否存在回路 
bool isCircleExistedInUndirectedGraph(vertex **graph, int vertex);

//该函数用于查找到回路时，将被查找到的回路打印出来 
void printOneCircleOfUndirectedGraph();



/*
	inputUtil的函数定义 
*/

//该函数从console获取图的输入并转换为图结构返回 
vertex **createGraphFromInput(bool isDirectedGraph);



/*
	util的函数定义 
*/

//去除输入中的回车符 
void removeEnterSymbol(); 

