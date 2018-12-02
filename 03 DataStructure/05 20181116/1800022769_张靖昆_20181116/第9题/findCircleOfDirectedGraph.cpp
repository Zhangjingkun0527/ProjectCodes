#include "definitions.h"
//����inputUtil�еĶ�����Ŀ���� 
extern int countOfVertexes;

//��������ͼ ���� ��visit�����ʶ
//������ͼ������ 
//visit[i]=0����ʾ����û�����ʣ� 
//visit[i]=1�����㱻�����һ�Ϊ�ж��Ƿ��ǻ�·�еĶ��㣻 
//visit[i]=2����ʾ��ǰ�����ѱ����ʣ����ҿ���ȷ���ö��㲻�����κ�һ����·��
//��Ϊ����������κ�һ����·����ô����������ʱ����������㷨һ�������ҵ���·
int *visitInDirectedGraph;

//���庯����ֻ���ڳ�ʼ����visit���� 
void initializeVisitArrInDirectedGraph(); 

//����һ��ջ�����ڼ�¼��ȱ���·���������һ�· 
int *stackInDirectedGraph = (int *)malloc(sizeof(int) * countOfVertexes);
int topInDirectedGraph = -1;

//�ú�����main������õĺ����������й��̵��ۺ� 
void findCircleOfDirectedGraph(){
	
	//��ȡͼ�ṹ 
	vertex **graph = createGraphFromInput(Graph_is_directed);
	//��ʼ��visit���� 
	initializeVisitArrInDirectedGraph();
	
	//����ѭ������ÿ����������鿴��· 
	//��Ϊ��������ͼ���������ܳ��ֵ��������������ͼ֮��û��ͨ·������һ����ͼ�л�·һ��û��
	//����ֻѡ��һ�����㣬����ܵó�������ж� 
	for(int i = 0; i < countOfVertexes; i++){
		//�����ǰ���㱻���ʹ�������������Ϊ���û�ҵ���·��������������ô��������Ҳ�Ҳ�����· 
		if(visitInDirectedGraph[i] == 2) continue;
		//�ҵ���·�󣬴�ӡ��·������ 
		if(isCircleExistedInDirectedGraph(graph, i)){
			printOneCircleOfDirectedGraph();
			return;
		}
	}
	printf("��ͼ�����ڻ�·��");
} 

//�ú������ڲ��ҵ���·ʱ���������ҵ��Ļ�·��ӡ���� 
void printOneCircleOfDirectedGraph(){
	printf("\n������ͼ���ڻ�·������һ����·�ǣ�\n"); 
	
	//ջ���Ķ����ǲ��һ�·�����У�ԭ���Ѿ�������ջ�еĶ��㣬ʹ�ù����˻�· 
	int start = stackInDirectedGraph[topInDirectedGraph];
	//��ǻ�·����λ�� 
	bool isFinded = false;
	for(int i = 0; i <= topInDirectedGraph; i++){
		if(isFinded){
			printf("%d ", stackInDirectedGraph[i]);
		}
		
		//������·�����isFindedΪfalse��Ӧ������isFindedΪtrue�����������·���
		if(stackInDirectedGraph[i] == start && !isFinded) {
			printf("%d ", stackInDirectedGraph[i]);
			isFinded = true;
		}
	}
} 


//�ú��������ж�ͼgraph�Ƿ���ڻ�· 
//�������������ȱ����ķ����ж��Ƿ���ڻ�· 
bool isCircleExistedInDirectedGraph(vertex **graph, int vertex){
	
	//��������ӽ�ջ 
	++topInDirectedGraph;
	stackInDirectedGraph[topInDirectedGraph] = vertex;
	
	//����ɵ�ǰ����������ص��ö��㣬�����ҵ���· 
	if(visitInDirectedGraph[vertex] == 1) return true;
	
	//�������ĳһ�������Ҳ�����·�Ľ�㣬Ӧ������false������ջ���ų� 
	if(visitInDirectedGraph[vertex] == 2) {
		--topInDirectedGraph;
		return false;
	}
	
	//�����ǰ����û�����ʣ�����visit[vertex]Ϊtrue�������ѷ��� 
	visitInDirectedGraph[vertex] = 1;
	
	//�����ǰ����������ͼ��û�г��ߣ���ôֱ�ӷ���false�����Ҵ�ջ���Ƴ����ұ��Ϊ���ڻ�·�� 
	if(graph[vertex] == NULL){
		visitInDirectedGraph[vertex] = 2; 
		--topInDirectedGraph;
		return false;
	}
	
	//����һ��û�����ʵĽ�㣬Ӧ��������ÿ���������ӵĶ������������ȱ��� 
	edge *p = graph[vertex]->first;
	while(p){
		// p->nextVertex != stack[top]��˵��������ͼ��������������֮����ܴ��������ߣ�ʹ�ö���i������j��
		//����j��û��������������ַ��ʶ���i������ʱ����i�Ѿ������ʣ���ʱ�����㷨����������������ҵ���·��i��j��i������Ȼ���ԡ�
		//Ϊ�˹����������������ǰ����Ľ�Ҫ��������һ��������ջ��������ڵĶ���(�����������Ϊ�ڱ�����ǰ����ı�ǰ����ǰ�����Ѿ�����ջ��)
		//��ͬ������ζ�Ż�������������Ӧ����ܡ� 
		if(topInDirectedGraph != 0 && p->nextVertex == stackInDirectedGraph[topInDirectedGraph - 1] ){
			p = p->next;
			continue;
		}
		
		//�����ǰ�������ӵĶ���û���ҵ���·���������ˣ�Ӧ������������һ���ߡ� 
		if(!isCircleExistedInDirectedGraph(graph, p->nextVertex)){
			p = p->next;
		}else return true;	
	}
	
	//����ڵ�ǰ���㴦û���ҵ���·�� ��û���ҵ������ý��Ļ�·�����ջ���Ƴ�
	--topInDirectedGraph;
	
	//����ɵ�ǰ��������Ҳ�����·����ô�ö���Ͳ����κλ�·�У����Ϊ2 
	visitInDirectedGraph[vertex] = 2;
	
	//��û���ҵ���·�Ƿ���false 
	return false;
}

//����˽�к�����ֻ���ڳ�ʼ��visit����
void initializeVisitArrInDirectedGraph(){
	visitInDirectedGraph = (int *)malloc(sizeof(int) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		visitInDirectedGraph[i] = 0;
	}
}
