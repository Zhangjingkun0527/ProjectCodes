#include "definitions.h"

//DAGͼ�еĶ�����Ŀ-��ʼ���壬�����ط�Ϊ���� 
extern int countOfVertexes;
//DAGͼ��Դ�㶥����±�
extern int startVertex;
//DAGͼ���յ㶥����±�
extern int endVertex;

//���ȱ�ʾ���ڽӱ�ṹ
extern vertex **graph_Stored_With_Adjacency_Table;

//�ñ��������������� findAllCriticalPathsAndCriticalEdges��������ʶ��Щ�ؼ�·���ϵĹؼ��ߣ�����ӽ���criticalEdges
edge *token = NULL;
//���ø�visit�������ڱ�ʶ 
int *visitOfEdges; 
//������ȱ������ڲ��Ҷ���ؼ�·�� 
void findAllCriticalPathsAndCriticalEdges(int vertex, vector<vector<int> > *v, int index, int *symbolOfCriticalActivity, 
										int *stack, int *top, vector<int> *criticalEdges);

//Ѱ�ҹؼ�·����ʹ����ȱ��������ж� 
//***ע�� ����һ����ά���飬��Ϊ�ؼ�·�������ж��*** 
//����һ��Ƕ�׵�vector����ά���飬ÿ�ж���һ���ؼ�·��
//vector��ά��������һ��vector<int>��criticalEdges���������Щ�������ٶȿ��Լӿ칤�� 
vector<vector<int> > findCriticalPath(int *criticalActivity){
	//����һ��ջ�����ڷ����¼�ؼ�·�� 
	int *stack = (int *)malloc(sizeof(int) * countOfVertexes);
	int top = -1;

	//���� symbolOfCriticalActivity��Ϊ�˱�ʶ��Ӧ�±궥���ǲ��ǹؼ�� 
	int *symbolOfCriticalActivity = (int *)malloc(sizeof(int) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++) {
		symbolOfCriticalActivity[i] = 0;
	}
	//�ǹؼ��������Ϊ1 
	for(int i = 1; i <= criticalActivity[0]; i++) {
		symbolOfCriticalActivity[criticalActivity[i]] = 1;
	}
	
	//��¼һЩ����ߣ������Щ�������ٶȿ��Լӿ칤�� 
	vector<int> criticalEdges; 
	//���ڲ�֪���ؼ�·���������������C++�ṩ��vector�洢�õ���·���ĵ�ַ 
	vector<vector<int> > v;
	//�ҵ����йؼ�·������vector�� 
	findAllCriticalPathsAndCriticalEdges(criticalActivity[1], &v, startVertex, symbolOfCriticalActivity, stack, &top, &criticalEdges);
	//����Ѱ�� criticalEdges���߼���Ѱ�ҹؼ�·�����߼����ƣ��Ӷ���Ѱ�ҵ����йؼ�·���󣬽�criticalEdges��ӽ����� 
	v.push_back(criticalEdges);
	return v;
}

void findAllCriticalPathsAndCriticalEdges(int vertex, vector<vector<int> > *v, int index, int *symbolOfCriticalActivity, 
										int *stack, int *top, vector<int> *criticalEdges){
	//�����ǰ�����ǹؼ����Ӧ������ջ�� 
	//������ǹؼ������ֱ�ӷ��أ���Ϊ�������ڹؼ�·���� 
	if(symbolOfCriticalActivity[vertex]){
		(*top)++;
		stack[*top] = vertex;
		//������˴�ʱ����ζ��token��ָʾ�ıߵ����˶��ǹؼ�����㡣 
		if(token != NULL) (*criticalEdges).push_back(token->index);
	}else return; 
	
	//�����ǰ����ʱ�յ㣬��ôһ��·�����ҵ��ˣ�����ջ�У��������׵�ַ���õ�vector�У���ֱ���˳����� 
	if(vertex == endVertex){		
		vector<int> temp;
		for(int i = 0; i <= (*top); i++){
			temp.push_back(stack[i]);
		}
		(*v).push_back(temp);
		//��ջ�����յ㶥���˳� 
		(*top)--;
		return;
	}
	
	//�Ե�ǰ�����ÿ�����Ӷ�����ͬ���Ĳ��� 
	edge *p = graph_Stored_With_Adjacency_Table[vertex]->first;
	while(p){
		//��¼��ǰ�ߣ������ж��ǲ��ǹؼ��� 
		token = p;
		findAllCriticalPathsAndCriticalEdges(p->nextVertex, v, index, symbolOfCriticalActivity, stack, top, criticalEdges);
		p = p->next;
	}
	
	//��ǰ�������������������ǹؼ����Ӧ����ջ���˳� 
	if(symbolOfCriticalActivity[vertex]){
		(*top)--;
	}
}

//�ú��������翪ʼʱ�������ʼʱ���ҵ��ؼ�����±꣬
//***ע�� ���ص�����ĵ�һ��ֵΪ�ؼ�������� ***
int *findCriticalActivity(int *beginningTime, int *endingTime){
	//����û�в������ݽṹ��������ͳ�ƹؼ�������� 
	int count = 0;
	for(int i = 0; i < countOfVertexes; i++){
		if(beginningTime[i] != endingTime[i]) continue;
		count++;
	}
	
	//Ϊ�ؼ���������ռ� 
	int *criticalActivity = (int *)malloc(sizeof(int) * (count + 1));
	criticalActivity[0] = count;
	
	//���ؼ������������ 
	int index = 1;
	for(int i = 0; i < countOfVertexes; i++){
		if(beginningTime[i] != endingTime[i]) continue;
		criticalActivity[index] = i;
		index++;
	}
	
	return criticalActivity;
}
