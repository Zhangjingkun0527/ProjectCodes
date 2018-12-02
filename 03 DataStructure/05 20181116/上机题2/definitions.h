#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

#define FILE_PATH_FOR_INPUT "C:\\Users\\Administrator\\Desktop\\data.txt"
#define FILE_PATH_FOR_OUTPUT "C:\\Users\\Administrator\\Desktop\\answer_1800022769.txt"
//ʹ�ü��±����ļ������Ҫ�滻����ļ���·���������������Ҳ�滻 
#define NOTEPAD_OPEN_FILE_COMMAND "Notepad.exe C:\\Users\\Administrator\\Desktop\\answer_1800022769.txt"

//�����Ȩ�ߵĽṹ��
typedef struct edge{
	int nextVertex;
	int weight;
	//AOE���бߵ��±꣬Ҳ�ǻ���±� 
	int index; 
	struct edge *next;
}edge;

//���嶥��ṹ�� 
typedef struct vertex{
	int vertex;
	//��¼�ö���ĳ��� 
	int outDegree;
	//��¼�ö������� 
	int inDegree;
	struct edge *first;
}vertex;

/*
	findCriticalActivityAndCriticalPath���ҹؼ���͹ؼ�·���ĺ������� 
*/
//Ѱ�ҹؼ�·��
//***ע�� ����һ����ά���飬��Ϊ�ؼ�·�������ж��*** 
//����һ��Ƕ�׵�vector����ά���飬ÿ�ж���һ���ؼ�·��
//vector��ά��������һ��vector<int>��criticalEdges���������Щ�������ٶȿ��Լӿ칤��
vector<vector<int> > findCriticalPath(int *criticalActivity);

//�ú��������翪ʼʱ�������ʼʱ���ҵ��ؼ�����±꣬
//***ע�� ���ص�����ĵ�һ��ֵΪ�ؼ�������� ***
//***���������е�2��ֵ��Դ��*** 
int *findCriticalActivity(int *beginningTime, int *endingTime);

/*
	getEndingTime����غ������壬���ڻ��ÿ�������������ʱ�� 
*/
//�ú�������getEndingTime������̣���������ʼʱ�� 
int *getEndingTime();
//�����ڽӱ����ÿ�����������ʱ�� 
int *calculateEndingTime(int *inverseTopoSerial);
//�������ڽӱ��õ�һ�����������У�����������緢��ʱ�� 
int *getInverseTopoSerial();


/*
	getBeginningTime�ĺ������壬���ڻ��ÿ�������������ʱ�� 
*/
//�ú�������getBeginningTime������̣��������翪ʼʱ�� 
int *getBeginningTime();
//�������ڽӱ����ÿ�������ķ���ʱ�䣬���õ���ͼ�ܹ� 
int *calculateBeginningTime(int *topoSerial);
//�����ڽӱ�õ�һ���������� 
int *getTopoSerial();



/*
	fileUtil�ĺ������� 
*/

//�ú����Ӵ��������ļ�·�����ļ�������ȡ�ļ��е����ݣ�ת��Ϊͼ�ṹ
//�ú�������2���ڽӱ�һ������ȱ�ʾ�����ڽӱ�һ���ǳ��ȱ�ʾ���ڽӱ� 
void createGraphFromFile(char *filePath); 

//��intһά����д���ļ� 
void writeForIntArr(int *arr, int start, int length, char *filePath, char *title);

//�������������ؼ�·��ʱ�õ���vector<vector<int> > ������ļ��� 
void writeForVectorArr(vector<int> v, char *filePath, char *title); 

/*
	util�ĺ������� 
*/
//����ϴ�ֵ
int max(int a, int b);
//�����Сֵ 
int min(int a, int b);
