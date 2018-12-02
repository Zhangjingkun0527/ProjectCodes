#include "definitions.h" 

//DAGͼ�еĶ�����Ŀ-��ʼ���壬�����ط�Ϊ���� 
int countOfVertexes;
//DAGͼ��Դ�㶥����±�-��ʼ���壬�����ط�Ϊ���� 
int startVertex;
//DAGͼ���յ㶥����±�-��ʼ���壬�����ط�Ϊ���� 
int endVertex;

//���ȱ�ʾ���ڽӱ�ṹ���壬�����Ǹýṹ�ĳ�ʼ���� 
vertex **graph_Stored_With_Adjacency_Table;
//��ȱ�ʾ�����ڽӱ�ṹ���壬�����Ǹýṹ�ĳ�ʼ����
vertex **graph_Stored_With_Inverse_Adjacency_Table; 

//�ú�������Ϊvertexes��ֵ����Ҫ�Ǽ���createGraphFromFile�����ĸ����� 
void setValue(vertex **vertexes, edge **temp, int vertex1, int vertex2, int weight, int index);

/*
	���벿�� 
*/
//�ú����Ӵ��������ļ�·�����ļ�������ȡ�ļ��е����ݣ�ת��Ϊ �ڽӱ� ��ʾ��ͼ�ṹ 
void createGraphFromFile(char *filePath){
	
	printf("\n������DAGͼ�Ķ�����Ŀ��Դ���±꣬�յ��±꣬��1-1-1����ʽ���룺\n");
	scanf("%d-%d-%d", &countOfVertexes, &startVertex, &endVertex);
	if(countOfVertexes <= 0) {
		printf("������Ŀ�������0��");
		return;	
	}
	
	//�������������飬��Ϊ�˼�¼ÿ����ĳһ����ı߱��������±߽��ʱ���һ������λ�ã��Ա�����
	//temp1�����ڼ�¼�ڽӱ�temp2���ڼ�¼���ڽӱ�
	edge **temp = (edge **)malloc(sizeof(edge *) * countOfVertexes);
	edge **tempForInverse = (edge **)malloc(sizeof(edge *) * countOfVertexes);
	//Ϊ������������ռ� 
	graph_Stored_With_Adjacency_Table = (vertex **)malloc(sizeof(vertex *) * countOfVertexes);
	graph_Stored_With_Inverse_Adjacency_Table = (vertex **)malloc(sizeof(vertex *) * countOfVertexes);
	
	//��ʼ���ĸ����飬Ϊ����ͼ�ṹ��ÿ������Ľṹ��������ֵ 
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
	
	//�����ļ�ָ�� 
	FILE *dataFile;
	if ((dataFile = fopen(filePath, "r")) == NULL){
        printf("�ļ���ʧ�ܣ�\n");
        return;
    }
    
    //ÿ�ζ�ȡһ�У�ÿ�����Ѿ��ϸ�涨ֻ����һ���ߵ������������ʽ ����1-����2-Ȩֵ-���±� 
    int vertex1, vertex2, weight, index;
    while((fscanf(dataFile, "%d-%d-%d-%d", &vertex1, &vertex2, &weight, &index)) != EOF) {
    	//Ϊ�ڽӱ�ֵ 
    	setValue(graph_Stored_With_Adjacency_Table, temp, vertex1, vertex2, weight, index);
    	graph_Stored_With_Adjacency_Table[vertex1]->outDegree++;
    	
    	//Ϊ���ڽӱ�ֵ 
    	setValue(graph_Stored_With_Inverse_Adjacency_Table, tempForInverse, vertex2, vertex1, weight, index);
    	graph_Stored_With_Inverse_Adjacency_Table[vertex2]->inDegree++; 
	}
	
	fclose(dataFile);
	free(temp);
	free(tempForInverse);
}

void setValue(vertex **vertexes, edge **temp, int vertex1, int vertex2, int weight, int index){
	//Ϊ��ǰ�߷���ռ� 
	edge *e = (edge *)malloc(sizeof(edge));
	e->nextVertex = vertex2;
	e->weight = weight;
	e->index = index;
	e->next = NULL;
		
	//���temp[vertex1]û�з���ռ䣬Ӧ�����䣬����vertexes[vertex1]��firstӦ����ֵ 
	if(temp[vertex1] == NULL){
		temp[vertex1] = (edge *)malloc(sizeof(edge));
		temp[vertex1] = e;
		//�·���ı߱���temp[vertex1]���ǵ�һ���� 
		vertexes[vertex1]->first = temp[vertex1];
	}else{
		//����temp[vertex1]��¼���Ƕ���vertex1�߱�����һ���ߣ��Ӷ�Ӧ�����±����ӵ�temp[vertex1]��next�� 
		temp[vertex1]->next = e;
		//����temp[vertex1]ָ��e�����¼���ı���vertex1�߱�����һ���� 
		temp[vertex1] = e;		
	}	
}


/*
	������� 
*/
//��intһά����д���ļ� 
void writeForIntArr(int *arr, int start, int length, char *filePath, char *title){
	//�����ļ�ָ�� 
	FILE *dataFile;
	if ((dataFile = fopen(filePath, "a")) == NULL){
        printf("�ļ���ʧ�ܣ�\n");
        return;
    }
    //������λ�ö�λ���ļ�ĩβ 
    fseek(dataFile, 0, SEEK_END);
    //�������ݱ���
    if(title[0] == '\0'){
    	fprintf(dataFile, "\n\n");
	}else{
		fprintf(dataFile, "\n%s\n", title);
	}
    
    //������� 
    for(int i = start; i < start + length; i++){
    	fprintf(dataFile, "%d ",arr[i]);
	}
	fprintf(dataFile, "\n");
	
	fclose(dataFile);
}

//�������������ؼ�·��ʱ���뵽vector<int>������������ļ��� 
void writeForVectorArr(vector<int> v, char *filePath, char *title){
	//�����ļ�ָ�� 
	FILE *dataFile;
	if ((dataFile = fopen(filePath, "a")) == NULL){
        printf("�ļ���ʧ�ܣ�\n");
        return;
    }
    //������λ�ö�λ���ļ�ĩβ 
    fseek(dataFile, 0, SEEK_END);
    //�������ݱ���
    if(title[0] == '\0'){
    	fprintf(dataFile, "\n\n");
	}else{
		fprintf(dataFile, "\n%s\n", title);
	}
    //������� 
    for(int i = 0; i < v.size(); i++){
    	fprintf(dataFile, "%d ", v[i]);
	}
	fprintf(dataFile, "\n");
	fclose(dataFile);
}
