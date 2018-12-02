#include "definitions.h"
//���嶥����
int countOfVertexes;

//�����˽�к��������ڸ�����ͱ߱�ֵ���򻯴����ظ��� 
void setValue(vertex **vertexes, edge **temp, int vertex1, int vertex2);

//�ú�����console��ȡͼ�����벢ת��Ϊͼ�ṹ���� 
vertex **createGraphFromInput(bool isDirectedGraph){
	
	if(isDirectedGraph){
		printf("**********��������ѡ����������ͼΪ����Ѱ�һ�·��***********\n\n");
	}else{
		printf("**********��������ѡ����������ͼΪ����Ѱ�һ�·��***********\n\n");
	}
	
	printf("�����붥�������(ע��ͼ�ж�������0��ʼ)��\n");
	scanf("%d", &countOfVertexes);
	
	//ȥ���س��� 
	removeEnterSymbol();
	
	//���䶥��һά���飬����ʼ��ΪNULL 
	vertex **vertexes = (vertex **)malloc(sizeof(vertex *) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		vertexes[i]  = NULL;
	}
		
	printf("\n���� �����±�-���Ӷ�����±� ��ʽ����ͼ������1-2������1�붥��2֮����һ���ߣ����������0-0��ʾ������\n");
	
	//���������±� 
	int index = 0;
	//ά��һ���ߵ�һά���飬�ֱ���ÿ�������Ӧ�����ڼ�¼ÿ������ı���ӵ��ĸ��ط��� 
	edge **temp = (edge **)malloc(sizeof(edge *) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		temp[i]  = NULL;
	}
	
	while(1){
		//����ͼ���� 
		int vertex1;
		int vertex2;
		scanf("%d-%d", &vertex1, &vertex2);
		if(vertex1 == 0 && vertex2 == 0) break;
		removeEnterSymbol();
		
		//����ͼ�У�����һ����Ҫ��ӽ�����������ı߱� 
		//������ͼֻ��Ҫֻ��Ҫ���һ�� 
		setValue(vertexes, temp, vertex1, vertex2);
		if(!isDirectedGraph){
			setValue(vertexes, temp, vertex2, vertex1);
		}
	}
	
	free(temp);
	return vertexes;
}

void setValue(vertex **vertexes, edge **temp, int vertex1, int vertex2){
	//Ϊ��ǰ�߷���ռ�
	edge *e = (edge *)malloc(sizeof(edge));
	e->nextVertex = vertex2;
	e->next = NULL;
		
	//�����ǰ����û�з���ռ䣬��Ӧ��Ϊ�����ռ䣬��Ϊ��Ӧ�߱����ռ� 
	if(vertexes[vertex1] == NULL){
		//Ϊ�������ռ䣬��ָ������ֵ 
		vertexes[vertex1] = (vertex *)malloc(sizeof(vertex));
		vertexes[vertex1]->vertex = vertex1;
		
		//����û�з��䶥��ռ䣬�Ӷ��߱�temp[vertex1]Ҳû����ռ䣬Ӧ�����䣬�����������e 
		temp[vertex1]  = (edge *)malloc(sizeof(edge));
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
