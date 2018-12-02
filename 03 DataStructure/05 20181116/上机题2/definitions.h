#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

#define FILE_PATH_FOR_INPUT "C:\\Users\\Administrator\\Desktop\\data.txt"
#define FILE_PATH_FOR_OUTPUT "C:\\Users\\Administrator\\Desktop\\answer_1800022769.txt"
//使用记事本打开文件，如果要替换输出文件的路径，请把下面命令也替换 
#define NOTEPAD_OPEN_FILE_COMMAND "Notepad.exe C:\\Users\\Administrator\\Desktop\\answer_1800022769.txt"

//定义带权边的结构体
typedef struct edge{
	int nextVertex;
	int weight;
	//AOE网中边的下标，也是活动的下标 
	int index; 
	struct edge *next;
}edge;

//定义顶点结构体 
typedef struct vertex{
	int vertex;
	//记录该顶点的出度 
	int outDegree;
	//记录该顶点的入度 
	int inDegree;
	struct edge *first;
}vertex;

/*
	findCriticalActivityAndCriticalPath查找关键活动和关键路径的函数定义 
*/
//寻找关键路径
//***注意 这是一个二维数组，因为关键路径可能有多个*** 
//返回一个嵌套的vector即二维数组，每行都是一个关键路径
//vector二维数组的最后一个vector<int>是criticalEdges，即提高这些活动的完成速度可以加快工程
vector<vector<int> > findCriticalPath(int *criticalActivity);

//该函数从最早开始时间和最晚开始时间找到关键活动的下标，
//***注意 返回的数组的第一个值为关键活动的数量 ***
//***并且数组中第2个值是源点*** 
int *findCriticalActivity(int *beginningTime, int *endingTime);

/*
	getEndingTime的相关函数定义，用于获得每个顶点的最晚发生时间 
*/
//该函数汇总getEndingTime处理过程，返回最晚开始时间 
int *getEndingTime();
//根据邻接表计算每个活动的最晚发生时间 
int *calculateEndingTime(int *inverseTopoSerial);
//根据逆邻接表，得到一个逆拓扑序列，方便计算最早发生时间 
int *getInverseTopoSerial();


/*
	getBeginningTime的函数定义，用于获得每个顶点的最晚发生时间 
*/
//该函数汇总getBeginningTime处理过程，返回最早开始时间 
int *getBeginningTime();
//根据逆邻接表计算每个活动最早的发生时间，所用到的图架构 
int *calculateBeginningTime(int *topoSerial);
//根据邻接表得到一个拓扑序列 
int *getTopoSerial();



/*
	fileUtil的函数定义 
*/

//该函数从传进来的文件路径打开文件，并读取文件中的内容，转化为图结构
//该函数创建2个邻接表，一个是入度表示的逆邻接表，一个是出度表示的邻接表 
void createGraphFromFile(char *filePath); 

//将int一维数组写入文件 
void writeForIntArr(int *arr, int start, int length, char *filePath, char *title);

//将本程序中求解关键路径时用到的vector<vector<int> > 输出到文件中 
void writeForVectorArr(vector<int> v, char *filePath, char *title); 

/*
	util的函数定义 
*/
//计算较大值
int max(int a, int b);
//计算较小值 
int min(int a, int b);
