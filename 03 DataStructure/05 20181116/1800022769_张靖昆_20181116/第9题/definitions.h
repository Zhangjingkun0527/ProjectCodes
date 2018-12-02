#include <cstdio>
#include <cstdlib>

#define Graph_is_directed 1
#define Graph_is_undirected 0

//�����ڽӱ�ķ�ʽ�洢ͼ�ṹ
//����߽ṹ�� 
typedef struct edge{
	int nextVertex;
	struct edge *next;
}edge;

//���嶥��ṹ�� 
typedef struct vertex{
	int vertex;
	struct edge *first;
}vertex;


/*
	findCircleOfDirectedGraph�ĺ������壬���߼�ģ�� 
*/

//�ú�����main������õĺ����������й��̵��ۺ� 
void findCircleOfDirectedGraph();

//�ú��������ж�ͼgraph�Ƿ���ڻ�· 
bool isCircleExistedInDirectedGraph(vertex **graph, int vertex);

//�ú������ڲ��ҵ���·ʱ���������ҵ��Ļ�·��ӡ���� 
void printOneCircleOfDirectedGraph();


/*
	findCircleOfUndirectedGraph�ĺ������壬���߼�ģ�� 
*/

//�ú�����main������õĺ����������й��̵��ۺ� 
void findCircleOfUndirectedGraph();

//�ú��������ж�ͼgraph�Ƿ���ڻ�· 
bool isCircleExistedInUndirectedGraph(vertex **graph, int vertex);

//�ú������ڲ��ҵ���·ʱ���������ҵ��Ļ�·��ӡ���� 
void printOneCircleOfUndirectedGraph();



/*
	inputUtil�ĺ������� 
*/

//�ú�����console��ȡͼ�����벢ת��Ϊͼ�ṹ���� 
vertex **createGraphFromInput(bool isDirectedGraph);



/*
	util�ĺ������� 
*/

//ȥ�������еĻس��� 
void removeEnterSymbol(); 

