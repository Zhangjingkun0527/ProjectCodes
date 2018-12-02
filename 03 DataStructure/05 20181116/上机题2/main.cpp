#include "definitions.h"

///DAG图中的顶点数目，首次定义在fileUtil中 
extern int countOfVertexes;


int main(int argc, char** argv) {
	printf("*****声明：文件路径以及文件名请全部使用英文，不要出现非ASCII字符，否则将打开失败！并且文件格式必须是TXT！*****\n\n"); 
	printf("文件中的每行只能有一条边的数据，以 顶点1-顶点2-权值-活动下标 的形式输入，例如1-2-10-0表示顶点1到顶点2可达，边权为10，且活动为a0。\n");
	printf("要求顶点和权值只能为int类型，且顶点下标从0开始！\n");
	
	/*
		从文件中获取数据，并创建图结构，FILE_PATH_FOR_INPUT是 definitions.h中 define为常量的用于文件输入的文件路径
		***请注意，文件路径不可以含有非法字符，只能使用全英文***
		***请在definitions.h中更改输入输出的文件路径***
	*/
	createGraphFromFile(FILE_PATH_FOR_INPUT);
	
	//求解最早开始时间 
	int *beginningTime = getBeginningTime();
	
	//求解最晚开始时间 
	int *endingTime = getEndingTime();
	
	//寻找关键顶点 
	int *criticalVertexes = findCriticalActivity(beginningTime, endingTime);
	
	//寻找关键路径及关键活动 
	vector<vector<int> > criticalPaths = findCriticalPath(criticalVertexes);
	
	//输出所有顶点的最早和最晚开始时间 
	writeForIntArr(beginningTime, 0, countOfVertexes, FILE_PATH_FOR_OUTPUT, "当前DAG图每个顶点的最早开始时间，从左到右按照顶点下标排序：");
	writeForIntArr(endingTime, 0, countOfVertexes, FILE_PATH_FOR_OUTPUT, "当前DAG图每个顶点的最晚开始时间，从左到右按照顶点下标排序：");
	
	//criticalVertexes的第一位是关键顶点的数量，从第二位开始是顶点下标 
	writeForIntArr(criticalVertexes, 1, criticalVertexes[0], FILE_PATH_FOR_OUTPUT, "当前DAG图的关键顶点，从左到右按照顶点下标排序：");
	//输出所有关键路径 
	for(int i =0 ; i < criticalPaths.size() - 1; i++){
		if(i == 0){
			writeForVectorArr(criticalPaths[i], FILE_PATH_FOR_OUTPUT, "当前DAG图的关键路径：");
		}else writeForVectorArr(criticalPaths[i], FILE_PATH_FOR_OUTPUT, "");
		
	}
	//输出所有关键活动 
	writeForVectorArr(criticalPaths[criticalPaths.size() - 1], FILE_PATH_FOR_OUTPUT, "提高下列活动可以提前完成整个工程，下列数据是边(活动)的下标：");
	
	printf("\n\n输出成功！");
	
	//用windows自带的记事本打开写入的文件 
	const char *command = NOTEPAD_OPEN_FILE_COMMAND;
	system(command);
	printf("\n\n");
	system("pause");
	return 0;
}
