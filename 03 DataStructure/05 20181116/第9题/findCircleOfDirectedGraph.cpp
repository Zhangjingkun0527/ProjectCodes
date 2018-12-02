#include "definitions.h"
//调用inputUtil中的顶点数目变量 
extern int countOfVertexes;

//定义有向图 顶点 的visit数组标识
//对有向图来讲： 
//visit[i]=0，表示顶点没被访问； 
//visit[i]=1代表顶点被访问且还为判断是否不是回路中的顶点； 
//visit[i]=2，表示当前顶点已被访问，并且可以确定该顶点不属于任何一个回路，
//因为如果它属于任何一个回路，那么当遍历到它时，深度优先算法一定可以找到回路
int *visitInDirectedGraph;

//定义函数，只用于初始化个visit数组 
void initializeVisitArrInDirectedGraph(); 

//设置一个栈，用于记录深度遍历路径，并查找回路 
int *stackInDirectedGraph = (int *)malloc(sizeof(int) * countOfVertexes);
int topInDirectedGraph = -1;

//该函数是main里面调用的函数，是所有过程的综合 
void findCircleOfDirectedGraph(){
	
	//获取图结构 
	vertex **graph = createGraphFromInput(Graph_is_directed);
	//初始化visit数组 
	initializeVisitArrInDirectedGraph();
	
	//设置循环，从每个顶点出发查看回路 
	//因为对于无向图来讲，可能出现的情况是有两个子图之间没有通路，但是一个子图有回路一个没有
	//若是只选择一个顶点，则可能得出错误的判断 
	for(int i = 0; i < countOfVertexes; i++){
		//如果当前顶点被访问过，则跳过，因为如果没找到回路而被遍历过，那么由它出发也找不到回路 
		if(visitInDirectedGraph[i] == 2) continue;
		//找到回路后，打印回路并返回 
		if(isCircleExistedInDirectedGraph(graph, i)){
			printOneCircleOfDirectedGraph();
			return;
		}
	}
	printf("该图不存在回路！");
} 

//该函数用于查找到回路时，将被查找到的回路打印出来 
void printOneCircleOfDirectedGraph(){
	printf("\n该无向图存在回路，其中一个回路是：\n"); 
	
	//栈顶的顶点是查找回路过程中，原本已经存在于栈中的顶点，使得构成了回路 
	int start = stackInDirectedGraph[topInDirectedGraph];
	//标记回路起点的位置 
	bool isFinded = false;
	for(int i = 0; i <= topInDirectedGraph; i++){
		if(isFinded){
			printf("%d ", stackInDirectedGraph[i]);
		}
		
		//遇到回路起点且isFinded为false，应当设置isFinded为true，并且输出回路起点
		if(stackInDirectedGraph[i] == start && !isFinded) {
			printf("%d ", stackInDirectedGraph[i]);
			isFinded = true;
		}
	}
} 


//该函数用于判断图graph是否存在回路 
//本题采用深度优先遍历的方法判断是否存在回路 
bool isCircleExistedInDirectedGraph(vertex **graph, int vertex){
	
	//将顶点添加进栈 
	++topInDirectedGraph;
	stackInDirectedGraph[topInDirectedGraph] = vertex;
	
	//如果由当前顶点出发返回到该顶点，代表找到回路 
	if(visitInDirectedGraph[vertex] == 1) return true;
	
	//如果遇到某一顶点是找不到回路的结点，应当返回false，并从栈中排出 
	if(visitInDirectedGraph[vertex] == 2) {
		--topInDirectedGraph;
		return false;
	}
	
	//如果当前顶点没被访问，则置visit[vertex]为true，代表已访问 
	visitInDirectedGraph[vertex] = 1;
	
	//如果当前顶点在有向图中没有出边，那么直接返回false，并且从栈中移除，且标记为不在回路中 
	if(graph[vertex] == NULL){
		visitInDirectedGraph[vertex] = 2; 
		--topInDirectedGraph;
		return false;
	}
	
	//对于一个没被访问的结点，应当对它的每条边所连接的顶点进行深度优先遍历 
	edge *p = graph[vertex]->first;
	while(p){
		// p->nextVertex != stack[top]的说明：有向图中由于两个顶点之间可能存在两条边，使得顶点i到顶点j后，
		//顶点j还没遍历其他顶点就又访问顶点i，而此时顶点i已经被访问，此时按照算法函数会结束，发现找到回路即i→j→i，这显然不对。
		//为了规避这种情况，如果当前顶点的将要遍历的下一个顶点与栈顶下面紧邻的顶点(下面紧邻是因为在遍历当前顶点的边前，当前顶点已经加入栈了)
		//相同，就意味着会出现上述情况，应当规避。 
		if(topInDirectedGraph != 0 && p->nextVertex == stackInDirectedGraph[topInDirectedGraph - 1] ){
			p = p->next;
			continue;
		}
		
		//如果当前边所连接的顶点没有找到回路，返回至此，应当继续查找下一条边。 
		if(!isCircleExistedInDirectedGraph(graph, p->nextVertex)){
			p = p->next;
		}else return true;	
	}
	
	//如果在当前顶点处没有找到回路， 即没有找到包含该结点的回路，则从栈中移除
	--topInDirectedGraph;
	
	//如果由当前顶点出发找不到回路，那么该顶点就不在任何回路中，标记为2 
	visitInDirectedGraph[vertex] = 2;
	
	//当没有找到回路是返回false 
	return false;
}

//定义私有函数，只用于初始化visit数组
void initializeVisitArrInDirectedGraph(){
	visitInDirectedGraph = (int *)malloc(sizeof(int) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		visitInDirectedGraph[i] = 0;
	}
}
