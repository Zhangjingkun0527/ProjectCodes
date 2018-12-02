#include "definitions.h" 

//引用fileUtil中定义的顶点数目 
extern int countOfVertexes; 
//DAG图的终点下标
extern int endVertex;

//引用fileUtil中定义的邻接表 
extern vertex **graph_Stored_With_Adjacency_Table;
//引用fileUtil中定义的逆邻接表 
extern vertex **graph_Stored_With_Inverse_Adjacency_Table;

//记录终点顶点的最早发生时间，同样也是终点顶点的最晚发生时间 
extern int endingTimeOfEndVertex;

/*
	被调用的函数
*/
//该函数汇总getEndingTime处理过程，返回最晚开始时间 
int *getEndingTime(){
	int *inverseTopSerial = getInverseTopoSerial();
	return calculateEndingTime(inverseTopSerial);
}

//根据邻接表计算每个活动的最晚发生时间 
int *calculateEndingTime(int *inverseTopoSerial){
	//创建最早发生时间数组，并初始化为0，由于每个活动都花费不为0的时间，因此可以初始为0 
	int *endingTime = (int *)malloc(sizeof(int) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		endingTime[i] = 0;
	}
	
	//计算每个活动的最早发生时间
	for(int i = 0; i < countOfVertexes; i++){
		//按照拓扑序列取出顶点 
		int vertex = inverseTopoSerial[i];
		//根据顶点的每条出边，进行最晚发生时间的计算 
		edge *p = graph_Stored_With_Adjacency_Table[vertex]->first;
		//将time初值定义为终点的最早发生时间，因为不会有其他顶点的发生时间比他还晚 
		int time = endingTimeOfEndVertex;
		while(p){
			//拿到p这条入边另一端的顶点号 
			int v = p->nextVertex;
			//计算最晚开始时间 
			time = min(time, endingTime[v] - p->weight);
			p = p->next; 
		}
		endingTime[vertex] = time;
	}

	return endingTime;
}

//根据逆邻接表，得到一个逆拓扑序列，方便计算最早发生时间 
int *getInverseTopoSerial(){
	//顶一个拓扑序列队列 
	queue<int> q;
	//为拓扑序列分配空间，没必要初始化 
	int *inverseTopoSerial = (int *)malloc(sizeof(int) * countOfVertexes);
	//用于指示inverseTopoSerial的指针 
	int count = -1;
	
	//先将出度为0的推入队列 
	for(int i = 0; i < countOfVertexes; i++){
		if(graph_Stored_With_Adjacency_Table[i]->outDegree != 0) continue;
		q.push(i);
	}
	//获取拓扑序列 
	while(!q.empty()) {
		//弹出队首的元素，并添加入拓扑序列中 
		int index = q.front();
		q.pop();
		count++; 
		inverseTopoSerial[count] = index;
		
		//从逆邻接表中拿到队首元素的第一条出边，然后拿到之后的边，并将它所连接的顶点在逆邻接表中的入度减1.
		edge *p = graph_Stored_With_Inverse_Adjacency_Table[index]->first;
		while(p){
			//边p连接的顶点在 邻接表 中的出度减1
			graph_Stored_With_Adjacency_Table[p->nextVertex]->outDegree--;
			//当这个顶点的出度减1后，如果它的出度变为0，则加入队列 
			if(graph_Stored_With_Adjacency_Table[p->nextVertex]->outDegree == 0){
				q.push(p->nextVertex);
			}
			
			p = p->next;
		}	
	}
	
	return inverseTopoSerial;
}
