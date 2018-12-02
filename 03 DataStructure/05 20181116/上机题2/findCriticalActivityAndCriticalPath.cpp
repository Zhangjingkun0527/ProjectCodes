#include "definitions.h"

//DAG图中的顶点数目-初始定义，其他地方为引用 
extern int countOfVertexes;
//DAG图的源点顶点的下标
extern int startVertex;
//DAG图的终点顶点的下标
extern int endVertex;

//出度表示的邻接表结构
extern vertex **graph_Stored_With_Adjacency_Table;

//该变量仅声明作用于 findAllCriticalPathsAndCriticalEdges，用来标识那些关键路径上的关键边，并添加进入criticalEdges
edge *token = NULL;
//设置该visit数组用于标识 
int *visitOfEdges; 
//定义深度遍历用于查找多个关键路径 
void findAllCriticalPathsAndCriticalEdges(int vertex, vector<vector<int> > *v, int index, int *symbolOfCriticalActivity, 
										int *stack, int *top, vector<int> *criticalEdges);

//寻找关键路径，使用深度遍历进行判断 
//***注意 这是一个二维数组，因为关键路径可能有多个*** 
//返回一个嵌套的vector即二维数组，每行都是一个关键路径
//vector二维数组的最后一个vector<int>是criticalEdges，即提高这些活动的完成速度可以加快工程 
vector<vector<int> > findCriticalPath(int *criticalActivity){
	//创建一个栈，用于方便记录关键路径 
	int *stack = (int *)malloc(sizeof(int) * countOfVertexes);
	int top = -1;

	//建立 symbolOfCriticalActivity，为了标识对应下标顶点是不是关键活动 
	int *symbolOfCriticalActivity = (int *)malloc(sizeof(int) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++) {
		symbolOfCriticalActivity[i] = 0;
	}
	//是关键活动的设置为1 
	for(int i = 1; i <= criticalActivity[0]; i++) {
		symbolOfCriticalActivity[criticalActivity[i]] = 1;
	}
	
	//记录一些活动即边，提高这些活动的完成速度可以加快工程 
	vector<int> criticalEdges; 
	//由于不知道关键路径的数量，因此用C++提供的vector存储得到的路径的地址 
	vector<vector<int> > v;
	//找到所有关键路径存入vector中 
	findAllCriticalPathsAndCriticalEdges(criticalActivity[1], &v, startVertex, symbolOfCriticalActivity, stack, &top, &criticalEdges);
	//由于寻找 criticalEdges的逻辑跟寻找关键路径的逻辑相似，从而在寻找到所有关键路径后，将criticalEdges添加进入结果 
	v.push_back(criticalEdges);
	return v;
}

void findAllCriticalPathsAndCriticalEdges(int vertex, vector<vector<int> > *v, int index, int *symbolOfCriticalActivity, 
										int *stack, int *top, vector<int> *criticalEdges){
	//如果当前顶点是关键活动，应当加入栈中 
	//如果不是关键活动，则直接返回，因为它不会在关键路径中 
	if(symbolOfCriticalActivity[vertex]){
		(*top)++;
		stack[*top] = vertex;
		//当进入此处时，意味着token所指示的边的两端都是关键活动顶点。 
		if(token != NULL) (*criticalEdges).push_back(token->index);
	}else return; 
	
	//如果当前顶点时终点，那么一条路径就找到了，存在栈中，将它的首地址放置到vector中，并直接退出函数 
	if(vertex == endVertex){		
		vector<int> temp;
		for(int i = 0; i <= (*top); i++){
			temp.push_back(stack[i]);
		}
		(*v).push_back(temp);
		//将栈顶的终点顶点退出 
		(*top)--;
		return;
	}
	
	//对当前顶点的每个连接顶点做同样的操作 
	edge *p = graph_Stored_With_Adjacency_Table[vertex]->first;
	while(p){
		//记录当前边，用于判断是不是关键边 
		token = p;
		findAllCriticalPathsAndCriticalEdges(p->nextVertex, v, index, symbolOfCriticalActivity, stack, top, criticalEdges);
		p = p->next;
	}
	
	//当前顶点遍历结束后，如果它是关键活动，应当从栈中退出 
	if(symbolOfCriticalActivity[vertex]){
		(*top)--;
	}
}

//该函数从最早开始时间和最晚开始时间找到关键活动的下标，
//***注意 返回的数组的第一个值为关键活动的数量 ***
int *findCriticalActivity(int *beginningTime, int *endingTime){
	//由于没有采用数据结构，这里先统计关键活动的数量 
	int count = 0;
	for(int i = 0; i < countOfVertexes; i++){
		if(beginningTime[i] != endingTime[i]) continue;
		count++;
	}
	
	//为关键活动数组分配空间 
	int *criticalActivity = (int *)malloc(sizeof(int) * (count + 1));
	criticalActivity[0] = count;
	
	//将关键活动加入数组中 
	int index = 1;
	for(int i = 0; i < countOfVertexes; i++){
		if(beginningTime[i] != endingTime[i]) continue;
		criticalActivity[index] = i;
		index++;
	}
	
	return criticalActivity;
}
