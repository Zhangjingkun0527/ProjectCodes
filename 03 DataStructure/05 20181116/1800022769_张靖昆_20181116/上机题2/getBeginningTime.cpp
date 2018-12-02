#include "definitions.h"

//引用fileUtil中定义的顶点数目 
extern int countOfVertexes; 
//DAG图的终点下标
extern int endVertex;

//引用fileUtil中定义的邻接表 
extern vertex **graph_Stored_With_Adjacency_Table;
//引用fileUtil中定义的逆邻接表 
extern vertex **graph_Stored_With_Inverse_Adjacency_Table;

//记录终点顶点的最早发生时间，同样也是终点顶点的最晚发生时间 - getEndingTime会使用到 
int endingTimeOfEndVertex;

/*
	被调用的函数 
*/
//该函数汇总getBeginningTime处理过程，返回最早开始时间 
int *getBeginningTime(){
	int *topSerial = getTopoSerial();
	return calculateBeginningTime(topSerial);
}

//计算每个活动最早的发生时间 
int *calculateBeginningTime(int *topoSerial){
	//创建最早发生时间数组，并初始化为0，由于每个活动都花费不为0的时间，因此可以初始为0 
	int *beginningTime = (int *)malloc(sizeof(int) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		beginningTime[i] = 0;
	}
	
	//计算每个活动的最早发生时间
	for(int i = 0; i < countOfVertexes; i++){
		//按照拓扑序列取出顶点 
		int vertex = topoSerial[i];
		//根据顶点的每条入边，进行最早发生时间的计算 
		edge *p = graph_Stored_With_Inverse_Adjacency_Table[vertex]->first;
		int time = 0;
		while(p){
			//拿到p这条入边另一端的顶点号 
			int v = p->nextVertex;
			time = max(time, beginningTime[v] + p->weight);
			p = p->next; 
		}
		beginningTime[vertex] = time;
	}
	//计算完毕最早开始时间后，给endingTimeOfEndVertex赋值 
	endingTimeOfEndVertex =  beginningTime[endVertex];
	return beginningTime;
	
}

//根据邻接表得到一个拓扑序列 
int *getTopoSerial(){
	//顶一个拓扑序列队列 
	queue<int> q;
	//为拓扑序列分配空间，没必要初始化 
	int *topoSerial = (int *)malloc(sizeof(int) * countOfVertexes);
	//用于指示topoSerial的指针 
	int count = -1;
	
	//先将入度为0的推入队列 
	for(int i = 0; i < countOfVertexes; i++){
		if(graph_Stored_With_Inverse_Adjacency_Table[i]->inDegree != 0) continue;
		q.push(i);
	}
	//获取拓扑序列 
	while(!q.empty()) {
		//弹出队首的元素，并添加入拓扑序列中 
		int index = q.front();
		q.pop();
		count++; 
		topoSerial[count] = index;
		
		//从邻接表中拿到队首元素的第一条出边，然后拿到之后的边，并将它所连接的顶点在逆邻接表中的入度减1.
		edge *p = graph_Stored_With_Adjacency_Table[index]->first;
		while(p){
			//边p连接的顶点在 逆邻接表 中的入度减1
			graph_Stored_With_Inverse_Adjacency_Table[p->nextVertex]->inDegree--;
			//当这个顶点的入度减1后，如果它的入度变为0，则加入队列 
			if(graph_Stored_With_Inverse_Adjacency_Table[p->nextVertex]->inDegree == 0){
				q.push(p->nextVertex);
			}
			
			p = p->next;
		}	
	}
	
	return topoSerial;
} 
