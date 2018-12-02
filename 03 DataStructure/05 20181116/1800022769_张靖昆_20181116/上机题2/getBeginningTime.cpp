#include "definitions.h"

//����fileUtil�ж���Ķ�����Ŀ 
extern int countOfVertexes; 
//DAGͼ���յ��±�
extern int endVertex;

//����fileUtil�ж�����ڽӱ� 
extern vertex **graph_Stored_With_Adjacency_Table;
//����fileUtil�ж�������ڽӱ� 
extern vertex **graph_Stored_With_Inverse_Adjacency_Table;

//��¼�յ㶥������緢��ʱ�䣬ͬ��Ҳ���յ㶥���������ʱ�� - getEndingTime��ʹ�õ� 
int endingTimeOfEndVertex;

/*
	�����õĺ��� 
*/
//�ú�������getBeginningTime������̣��������翪ʼʱ�� 
int *getBeginningTime(){
	int *topSerial = getTopoSerial();
	return calculateBeginningTime(topSerial);
}

//����ÿ�������ķ���ʱ�� 
int *calculateBeginningTime(int *topoSerial){
	//�������緢��ʱ�����飬����ʼ��Ϊ0������ÿ��������Ѳ�Ϊ0��ʱ�䣬��˿��Գ�ʼΪ0 
	int *beginningTime = (int *)malloc(sizeof(int) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		beginningTime[i] = 0;
	}
	
	//����ÿ��������緢��ʱ��
	for(int i = 0; i < countOfVertexes; i++){
		//������������ȡ������ 
		int vertex = topoSerial[i];
		//���ݶ����ÿ����ߣ��������緢��ʱ��ļ��� 
		edge *p = graph_Stored_With_Inverse_Adjacency_Table[vertex]->first;
		int time = 0;
		while(p){
			//�õ�p���������һ�˵Ķ���� 
			int v = p->nextVertex;
			time = max(time, beginningTime[v] + p->weight);
			p = p->next; 
		}
		beginningTime[vertex] = time;
	}
	//����������翪ʼʱ��󣬸�endingTimeOfEndVertex��ֵ 
	endingTimeOfEndVertex =  beginningTime[endVertex];
	return beginningTime;
	
}

//�����ڽӱ�õ�һ���������� 
int *getTopoSerial(){
	//��һ���������ж��� 
	queue<int> q;
	//Ϊ�������з���ռ䣬û��Ҫ��ʼ�� 
	int *topoSerial = (int *)malloc(sizeof(int) * countOfVertexes);
	//����ָʾtopoSerial��ָ�� 
	int count = -1;
	
	//�Ƚ����Ϊ0��������� 
	for(int i = 0; i < countOfVertexes; i++){
		if(graph_Stored_With_Inverse_Adjacency_Table[i]->inDegree != 0) continue;
		q.push(i);
	}
	//��ȡ�������� 
	while(!q.empty()) {
		//�������׵�Ԫ�أ������������������ 
		int index = q.front();
		q.pop();
		count++; 
		topoSerial[count] = index;
		
		//���ڽӱ����õ�����Ԫ�صĵ�һ�����ߣ�Ȼ���õ�֮��ıߣ������������ӵĶ��������ڽӱ��е���ȼ�1.
		edge *p = graph_Stored_With_Adjacency_Table[index]->first;
		while(p){
			//��p���ӵĶ����� ���ڽӱ� �е���ȼ�1
			graph_Stored_With_Inverse_Adjacency_Table[p->nextVertex]->inDegree--;
			//������������ȼ�1�����������ȱ�Ϊ0���������� 
			if(graph_Stored_With_Inverse_Adjacency_Table[p->nextVertex]->inDegree == 0){
				q.push(p->nextVertex);
			}
			
			p = p->next;
		}	
	}
	
	return topoSerial;
} 
