#include "definitions.h"
//调用inputUtil中的顶点数目变量 
extern int countOfVertexes;

//定义visit数组标识
int *visitInUndirectedGraph;
//定义私有函数，只用于初始化visit数组 
void initializeVisitArrInUndirectedGraph(); 

//设置一个栈，用于记录深度遍历路径，并查找回路 
int *stackInUndirectedGraph = (int *)malloc(sizeof(int) * countOfVertexes);
int topInUndirectedGraph = -1;

//该函数是main里面调用的函数，是所有过程的综合 
void findCircleOfUndirectedGraph(){
	
	//获取图结构 
	vertex **graph = createGraphFromInput(Graph_is_undirected);
	//初始化visit数组 
	initializeVisitArrInUndirectedGraph();
	
	//设置循环，从每个顶点出发查看回路 
	//因为对于无向图来讲，可能出现的情况是有两个子图之间没有通路，但是一个子图有回路一个没有
	//若是只选择一个顶点，则可能得出错误的判断 
	for(int i = 0; i < countOfVertexes; i++){
		//如果当前顶点被访问过，则跳过，因为如果没找到回路而被遍历过，那么由它出发也找不到回路 
		if(visitInUndirectedGraph[i]) continue;
		//找到回路后，打印回路并返回 
		if(isCircleExistedInUndirectedGraph(graph, i)){
			printOneCircleOfUndirectedGraph();
			return;
		}
	}
	printf("该图不存在回路！");
} 

//该函数用于查找到回路时，将被查找到的回路打印出来 
void printOneCircleOfUndirectedGraph(){
	printf("\n该有向图存在回路，其中一个回路是：\n"); 
	
	//栈顶的顶点是查找回路过程中，原本已经存在于栈中的顶点，使得构成了回路 
	int start = stackInUndirectedGraph[topInUndirectedGraph];
	//标记回路起点的位置 
	bool isFinded = false;
	for(int i = 0; i <= topInUndirectedGraph; i++){
		if(isFinded){
			printf("%d ", stackInUndirectedGraph[i]);
		}
		
		//遇到回路起点且isFinded为false，应当设置isFinded为true，并且输出回路起点
		if(stackInUndirectedGraph[i] == start && !isFinded) {
			printf("%d ", stackInUndirectedGraph[i]);
			isFinded = true;
		}
	}
} 

//该函数用于判断图graph是否存在回路 
//本题采用深度优先遍历的方法判断是否存在回路 
bool isCircleExistedInUndirectedGraph(vertex **graph, int vertex){
	
	//将顶点添加进栈 
	++topInUndirectedGraph;
	stackInUndirectedGraph[topInUndirectedGraph] = vertex;
	
	//当某一顶点被访问过，那么回路找到。 
	if(visitInUndirectedGraph[vertex]) return true; 
	
	//如果当前顶点没被访问，则置visit[vertex]为true，代表已访问 
	visitInUndirectedGraph[vertex] = true;
	
	//如果当前顶点在有向图中没有出边，那么直接返回false，并且从栈中移除
	if(graph[vertex] == NULL)  {
		--topInUndirectedGraph;
		return false;
	}
	
	//对于一个没被访问的结点，应当对它的每条边所连接的顶点进行深度优先遍历
	edge *p = graph[vertex]->first;
	while(p){
		// p->nextVertex != stack[top]的说明：无向图中由于一条边会添加到两个顶点的边表中，可能出现有顶点i到顶点j后，
		//顶点j还没遍历其他顶点就又访问顶点i，而此时顶点i已经被访问，此时按照算法函数会结束，发现找到回路即i→j→i，这显然不对。
		//为了规避这种情况，如果当前顶点的将要遍历的下一个顶点与栈顶下面紧邻的顶点(下面紧邻是因为在遍历当前顶点的边前，当前顶点已经加入栈了)
		//相同，就意味着会出现上述情况，应当规避。 
		if(topInUndirectedGraph != 0 && p->nextVertex == stackInUndirectedGraph[topInUndirectedGraph - 1] ){
			p = p->next;
			continue;
		}
		
		//如果当前边所连接的顶点没有找到回路，返回至此，应当继续查找下一条边。 
		if(!isCircleExistedInUndirectedGraph(graph, p->nextVertex)){
			p = p->next;
		}else return true;	
	}
	
	//如果在当前顶点处没有找到回路， 即没有找到包含该结点的回路，则从栈中移除
	--topInUndirectedGraph;
	//当没有找到回路是返回false 
	return false;
}

//定义私有函数，只用于初始化visit数组
void initializeVisitArrInUndirectedGraph(){
	visitInUndirectedGraph = (int *)malloc(sizeof(int) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		visitInUndirectedGraph[i] = 0;
	}
}
