#include "definitions.h" 

//DAG图中的顶点数目-初始定义，其他地方为引用 
int countOfVertexes;
//DAG图的源点顶点的下标-初始定义，其他地方为引用 
int startVertex;
//DAG图的终点顶点的下标-初始定义，其他地方为引用 
int endVertex;

//出度表示的邻接表结构定义，这里是该结构的初始定义 
vertex **graph_Stored_With_Adjacency_Table;
//入度表示的逆邻接表结构定义，这里是该结构的初始定义
vertex **graph_Stored_With_Inverse_Adjacency_Table; 

//该函数用于为vertexes赋值，主要是减轻createGraphFromFile函数的复杂性 
void setValue(vertex **vertexes, edge **temp, int vertex1, int vertex2, int weight, int index);

/*
	输入部分 
*/
//该函数从传进来的文件路径打开文件，并读取文件中的内容，转化为 邻接表 表示的图结构 
void createGraphFromFile(char *filePath){
	
	printf("\n请输入DAG图的顶点数目，源点下标，终点下标，以1-1-1的形式输入：\n");
	scanf("%d-%d-%d", &countOfVertexes, &startVertex, &endVertex);
	if(countOfVertexes <= 0) {
		printf("顶点数目必须大于0！");
		return;	
	}
	
	//定义两个边数组，是为了记录每次在某一定点的边表中链接新边结点时最后一个结点的位置，以便链接
	//temp1是用于记录邻接表，temp2用于记录逆邻接表
	edge **temp = (edge **)malloc(sizeof(edge *) * countOfVertexes);
	edge **tempForInverse = (edge **)malloc(sizeof(edge *) * countOfVertexes);
	//为两个顶点表分配空间 
	graph_Stored_With_Adjacency_Table = (vertex **)malloc(sizeof(vertex *) * countOfVertexes);
	graph_Stored_With_Inverse_Adjacency_Table = (vertex **)malloc(sizeof(vertex *) * countOfVertexes);
	
	//初始化四个数组，为两个图结构的每个顶点的结构变量赋初值 
	for(int i = 0; i < countOfVertexes; i++){
		graph_Stored_With_Adjacency_Table[i] = (vertex *)malloc(sizeof(vertex));
		graph_Stored_With_Adjacency_Table[i]->first = NULL;
		graph_Stored_With_Adjacency_Table[i]->inDegree = 0;
		graph_Stored_With_Adjacency_Table[i]->outDegree = 0;
		graph_Stored_With_Adjacency_Table[i]->vertex = i;
		
		graph_Stored_With_Inverse_Adjacency_Table[i] = (vertex *)malloc(sizeof(vertex));
		graph_Stored_With_Inverse_Adjacency_Table[i]->first = NULL; 
		graph_Stored_With_Inverse_Adjacency_Table[i]->inDegree = 0;
		graph_Stored_With_Inverse_Adjacency_Table[i]->outDegree = 0;
		graph_Stored_With_Inverse_Adjacency_Table[i]->vertex = i;
		
		temp[i] = NULL;
		tempForInverse[i] = NULL;
	}
	
	//定义文件指针 
	FILE *dataFile;
	if ((dataFile = fopen(filePath, "r")) == NULL){
        printf("文件打开失败！\n");
        return;
    }
    
    //每次读取一行，每行中已经严格规定只能是一条边的数据且满足格式 顶点1-顶点2-权值-边下标 
    int vertex1, vertex2, weight, index;
    while((fscanf(dataFile, "%d-%d-%d-%d", &vertex1, &vertex2, &weight, &index)) != EOF) {
    	//为邻接表赋值 
    	setValue(graph_Stored_With_Adjacency_Table, temp, vertex1, vertex2, weight, index);
    	graph_Stored_With_Adjacency_Table[vertex1]->outDegree++;
    	
    	//为逆邻接表赋值 
    	setValue(graph_Stored_With_Inverse_Adjacency_Table, tempForInverse, vertex2, vertex1, weight, index);
    	graph_Stored_With_Inverse_Adjacency_Table[vertex2]->inDegree++; 
	}
	
	fclose(dataFile);
	free(temp);
	free(tempForInverse);
}

void setValue(vertex **vertexes, edge **temp, int vertex1, int vertex2, int weight, int index){
	//为当前边分配空间 
	edge *e = (edge *)malloc(sizeof(edge));
	e->nextVertex = vertex2;
	e->weight = weight;
	e->index = index;
	e->next = NULL;
		
	//如果temp[vertex1]没有分配空间，应当分配，并且vertexes[vertex1]的first应当赋值 
	if(temp[vertex1] == NULL){
		temp[vertex1] = (edge *)malloc(sizeof(edge));
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


/*
	输出部分 
*/
//将int一维数组写入文件 
void writeForIntArr(int *arr, int start, int length, char *filePath, char *title){
	//定义文件指针 
	FILE *dataFile;
	if ((dataFile = fopen(filePath, "a")) == NULL){
        printf("文件打开失败！\n");
        return;
    }
    //将插入位置定位在文件末尾 
    fseek(dataFile, 0, SEEK_END);
    //输入数据标题
    if(title[0] == '\0'){
    	fprintf(dataFile, "\n\n");
	}else{
		fprintf(dataFile, "\n%s\n", title);
	}
    
    //输出数据 
    for(int i = start; i < start + length; i++){
    	fprintf(dataFile, "%d ",arr[i]);
	}
	fprintf(dataFile, "\n");
	
	fclose(dataFile);
}

//将本程序中求解关键路径时存入到vector<int>的数据输出到文件中 
void writeForVectorArr(vector<int> v, char *filePath, char *title){
	//定义文件指针 
	FILE *dataFile;
	if ((dataFile = fopen(filePath, "a")) == NULL){
        printf("文件打开失败！\n");
        return;
    }
    //将插入位置定位在文件末尾 
    fseek(dataFile, 0, SEEK_END);
    //输入数据标题
    if(title[0] == '\0'){
    	fprintf(dataFile, "\n\n");
	}else{
		fprintf(dataFile, "\n%s\n", title);
	}
    //输出数据 
    for(int i = 0; i < v.size(); i++){
    	fprintf(dataFile, "%d ", v[i]);
	}
	fprintf(dataFile, "\n");
	fclose(dataFile);
}
