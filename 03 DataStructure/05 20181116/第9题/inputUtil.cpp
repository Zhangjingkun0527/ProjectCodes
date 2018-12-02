#include "definitions.h"
//定义顶点数
int countOfVertexes;

//定义该私有函数，用于给顶点和边表赋值，简化代码重复度 
void setValue(vertex **vertexes, edge **temp, int vertex1, int vertex2);

//该函数从console获取图的输入并转换为图结构返回 
vertex **createGraphFromInput(bool isDirectedGraph){
	
	if(isDirectedGraph){
		printf("**********声明：您选择了以有向图为基础寻找回路！***********\n\n");
	}else{
		printf("**********声明：您选择了以无向图为基础寻找回路！***********\n\n");
	}
	
	printf("请输入顶点的数量(注意图中顶点必须从0开始)：\n");
	scanf("%d", &countOfVertexes);
	
	//去除回车符 
	removeEnterSymbol();
	
	//分配顶点一维数组，并初始化为NULL 
	vertex **vertexes = (vertex **)malloc(sizeof(vertex *) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		vertexes[i]  = NULL;
	}
		
	printf("\n请以 顶点下标-连接顶点的下标 格式输入图，例如1-2代表顶点1与顶点2之间有一条边，最后请输入0-0表示结束：\n");
	
	//顶点数组下标 
	int index = 0;
	//维护一个边的一维数组，分别于每个顶点对应，用于记录每个顶点的边添加到哪个地方了 
	edge **temp = (edge **)malloc(sizeof(edge *) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		temp[i]  = NULL;
	}
	
	while(1){
		//输入图数据 
		int vertex1;
		int vertex2;
		scanf("%d-%d", &vertex1, &vertex2);
		if(vertex1 == 0 && vertex2 == 0) break;
		removeEnterSymbol();
		
		//无向图中，对于一条边要添加进入两个顶点的边表 
		//而有向图只需要只需要添加一次 
		setValue(vertexes, temp, vertex1, vertex2);
		if(!isDirectedGraph){
			setValue(vertexes, temp, vertex2, vertex1);
		}
	}
	
	free(temp);
	return vertexes;
}

void setValue(vertex **vertexes, edge **temp, int vertex1, int vertex2){
	//为当前边分配空间
	edge *e = (edge *)malloc(sizeof(edge));
	e->nextVertex = vertex2;
	e->next = NULL;
		
	//如果当前顶点没有分配空间，则应当为其分配空间，且为对应边表分配空间 
	if(vertexes[vertex1] == NULL){
		//为顶点分配空间，并指定顶点值 
		vertexes[vertex1] = (vertex *)malloc(sizeof(vertex));
		vertexes[vertex1]->vertex = vertex1;
		
		//由于没有分配顶点空间，从而边表temp[vertex1]也没分配空间，应当分配，并且另其等于e 
		temp[vertex1]  = (edge *)malloc(sizeof(edge));
		temp[vertex1] = e;
		
		//新分配的边表结点temp[vertex1]就是第一条边 
		vertexes[vertex1]->first = temp[vertex1];
	}else{
		//由于temp[vertex1]记录的是顶点vertex1边表的最后一个边，从而应当将新边链接到temp[vertex1]的next上 
		temp[vertex1]->next = e;
		//并将temp[vertex1]指向e，即新加入的边是vertex1边表的最后一个边 
		temp[vertex1] = e;	
	} 
} 
