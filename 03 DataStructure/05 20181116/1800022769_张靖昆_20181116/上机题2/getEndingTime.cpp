#include "definitions.h" 

//����fileUtil�ж���Ķ�����Ŀ 
extern int countOfVertexes; 
//DAGͼ���յ��±�
extern int endVertex;

//����fileUtil�ж�����ڽӱ� 
extern vertex **graph_Stored_With_Adjacency_Table;
//����fileUtil�ж�������ڽӱ� 
extern vertex **graph_Stored_With_Inverse_Adjacency_Table;

//��¼�յ㶥������緢��ʱ�䣬ͬ��Ҳ���յ㶥���������ʱ�� 
extern int endingTimeOfEndVertex;

/*
	�����õĺ���
*/
//�ú�������getEndingTime������̣���������ʼʱ�� 
int *getEndingTime(){
	int *inverseTopSerial = getInverseTopoSerial();
	return calculateEndingTime(inverseTopSerial);
}

//�����ڽӱ����ÿ�����������ʱ�� 
int *calculateEndingTime(int *inverseTopoSerial){
	//�������緢��ʱ�����飬����ʼ��Ϊ0������ÿ��������Ѳ�Ϊ0��ʱ�䣬��˿��Գ�ʼΪ0 
	int *endingTime = (int *)malloc(sizeof(int) * countOfVertexes);
	for(int i = 0; i < countOfVertexes; i++){
		endingTime[i] = 0;
	}
	
	//����ÿ��������緢��ʱ��
	for(int i = 0; i < countOfVertexes; i++){
		//������������ȡ������ 
		int vertex = inverseTopoSerial[i];
		//���ݶ����ÿ�����ߣ�����������ʱ��ļ��� 
		edge *p = graph_Stored_With_Adjacency_Table[vertex]->first;
		//��time��ֵ����Ϊ�յ�����緢��ʱ�䣬��Ϊ��������������ķ���ʱ��������� 
		int time = endingTimeOfEndVertex;
		while(p){
			//�õ�p���������һ�˵Ķ���� 
			int v = p->nextVertex;
			//��������ʼʱ�� 
			time = min(time, endingTime[v] - p->weight);
			p = p->next; 
		}
		endingTime[vertex] = time;
	}

	return endingTime;
}

//�������ڽӱ��õ�һ�����������У�����������緢��ʱ�� 
int *getInverseTopoSerial(){
	//��һ���������ж��� 
	queue<int> q;
	//Ϊ�������з���ռ䣬û��Ҫ��ʼ�� 
	int *inverseTopoSerial = (int *)malloc(sizeof(int) * countOfVertexes);
	//����ָʾinverseTopoSerial��ָ�� 
	int count = -1;
	
	//�Ƚ�����Ϊ0��������� 
	for(int i = 0; i < countOfVertexes; i++){
		if(graph_Stored_With_Adjacency_Table[i]->outDegree != 0) continue;
		q.push(i);
	}
	//��ȡ�������� 
	while(!q.empty()) {
		//�������׵�Ԫ�أ������������������ 
		int index = q.front();
		q.pop();
		count++; 
		inverseTopoSerial[count] = index;
		
		//�����ڽӱ����õ�����Ԫ�صĵ�һ�����ߣ�Ȼ���õ�֮��ıߣ������������ӵĶ��������ڽӱ��е���ȼ�1.
		edge *p = graph_Stored_With_Inverse_Adjacency_Table[index]->first;
		while(p){
			//��p���ӵĶ����� �ڽӱ� �еĳ��ȼ�1
			graph_Stored_With_Adjacency_Table[p->nextVertex]->outDegree--;
			//���������ĳ��ȼ�1��������ĳ��ȱ�Ϊ0���������� 
			if(graph_Stored_With_Adjacency_Table[p->nextVertex]->outDegree == 0){
				q.push(p->nextVertex);
			}
			
			p = p->next;
		}	
	}
	
	return inverseTopoSerial;
}
