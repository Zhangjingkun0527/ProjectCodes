#include "definitions.h"
//����inputUtil�еĶ�����Ŀ���� 
extern int countOfVertexes;

//����visit�����ʶ
int *visitInUndirectedGraph;
//����˽�к�����ֻ���ڳ�ʼ��visit���� 
void initializeVisitArrInUndirectedGraph(); 

//����һ��ջ�����ڼ�¼��ȱ���·���������һ�· 
int *stackInUndirectedGraph = (int *)malloc(sizeof(int) * countOfVertexes);
int topInUndirectedGraph = -1;

//�ú�����main������õĺ����������й��̵��ۺ� 
void findCircleOfUndirectedGraph(){
	
	//��ȡͼ�ṹ 
	vertex **graph = createGraphFromInput(Graph_is_undirected);
	//��ʼ��visit���� 
	initializeVisitArrInUndirectedGraph();
	
	//����ѭ������ÿ����������鿴��· 
	//��Ϊ��������ͼ���������ܳ��ֵ��������������ͼ֮��û��ͨ·������һ����ͼ�л�·һ��û��
	//����ֻѡ��һ�����㣬����ܵó�������ж� 
	for(int i = 0; i < countOfVertexes; i++){
		//�����ǰ���㱻���ʹ�������������Ϊ���û�ҵ���·��������������ô��������Ҳ�Ҳ�����· 
		if(visitInUndirectedGraph[i]) continue;
		//�ҵ���·�󣬴�ӡ��·������ 
		if(isCircleExistedInUndirectedGraph(graph, i)){
			printOneCircleOfUndirectedGraph();
			return;
		}
	}
	printf("��ͼ�����ڻ�·��");
} 

//�ú������ڲ��ҵ���·ʱ���������ҵ��Ļ�·��ӡ���� 
void printOneCircleOfUndirectedGraph(){
	printf("\n������ͼ���ڻ�·������һ����·�ǣ�\n"); 
	
	//ջ���Ķ����ǲ��һ�·�����У�ԭ���Ѿ�������ջ�еĶ��㣬ʹ�ù����˻�· 
	int start = stackInUndirectedGraph[topInUndirectedGraph];
	//��ǻ�·����λ�� 
	bool isFinded = false;
	for(int i = 0; i <= topInUndirectedGraph; i++){
		if(isFinded){
			printf("%d ", stackInUndirectedGraph[i]);
		}
		
		//������·�����isFindedΪfalse��Ӧ������isFindedΪtrue�����������·���
		if(stackInUndirectedGraph[i] == start && !isFinded) {
			printf("%d ", stackInUndirectedGraph[i]);
			isFinded = true;
		}
	}
} 

//�ú��������ж�ͼgraph�Ƿ���ڻ�· 
//�������������ȱ����ķ����ж��Ƿ���ڻ�· 
bool isCircleExistedInUndirectedGraph(vertex **graph, int vertex){
	
	//��������ӽ�ջ 
	++topInUndirectedGraph;
	stackInUndirectedGraph[topInUndirectedGraph] = vertex;
	
	//��ĳһ���㱻���ʹ�����ô��·�ҵ��� 
	if(visitInUndirectedGraph[vertex]) return true; 
	
	//�����ǰ����û�����ʣ�����visit[vertex]Ϊtrue�������ѷ��� 
	visitInUndirectedGraph[vertex] = true;
	
	//�����ǰ����������ͼ��û�г��ߣ���ôֱ�ӷ���false�����Ҵ�ջ���Ƴ�
	if(graph[vertex] == NULL)  {
		--topInUndirectedGraph;
		return false;
	}
	
	//����һ��û�����ʵĽ�㣬Ӧ��������ÿ���������ӵĶ������������ȱ���
	edge *p = graph[vertex]->first;
	while(p){
		// p->nextVertex != stack[top]��˵��������ͼ������һ���߻���ӵ���������ı߱��У����ܳ����ж���i������j��
		//����j��û��������������ַ��ʶ���i������ʱ����i�Ѿ������ʣ���ʱ�����㷨����������������ҵ���·��i��j��i������Ȼ���ԡ�
		//Ϊ�˹����������������ǰ����Ľ�Ҫ��������һ��������ջ��������ڵĶ���(�����������Ϊ�ڱ�����ǰ����ı�ǰ����ǰ�����Ѿ�����ջ��)
		//��ͬ������ζ�Ż�������������Ӧ����ܡ� 
		if(topInUndirectedGraph != 0 && p->nextVertex == stackInUndirectedGraph[topInUndirectedGraph - 1] ){
			p = p->next;
			continue;
		}
		
		//�����ǰ�������ӵĶ���û���ҵ���·���������ˣ�Ӧ������������һ���ߡ� 
		if(!isCircleExistedInUndirectedGraph(graph, p->nextVertex)){
			p = p->next;
		}else return true;	
	}
	
	//����ڵ�ǰ���㴦û���ҵ���·�� ��û���ҵ������ý��Ļ�·�����ջ���Ƴ�
	--topInUndirectedGraph;
	//��û���ҵ���·�Ƿ���false 
	return false;
}

//����˽�к�����ֻ���ڳ�ʼ��visit����
void initializeVisitArrInUndirectedGraph(){
	visitInUndirectedGraph = (int *)malloc(sizeof(int) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		visitInUndirectedGraph[i] = 0;
	}
}
