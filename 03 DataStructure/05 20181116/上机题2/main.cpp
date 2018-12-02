#include "definitions.h"

///DAGͼ�еĶ�����Ŀ���״ζ�����fileUtil�� 
extern int countOfVertexes;


int main(int argc, char** argv) {
	printf("*****�������ļ�·���Լ��ļ�����ȫ��ʹ��Ӣ�ģ���Ҫ���ַ�ASCII�ַ������򽫴�ʧ�ܣ������ļ���ʽ������TXT��*****\n\n"); 
	printf("�ļ��е�ÿ��ֻ����һ���ߵ����ݣ��� ����1-����2-Ȩֵ-��±� ����ʽ���룬����1-2-10-0��ʾ����1������2�ɴ��ȨΪ10���һΪa0��\n");
	printf("Ҫ�󶥵��Ȩֵֻ��Ϊint���ͣ��Ҷ����±��0��ʼ��\n");
	
	/*
		���ļ��л�ȡ���ݣ�������ͼ�ṹ��FILE_PATH_FOR_INPUT�� definitions.h�� defineΪ�����������ļ�������ļ�·��
		***��ע�⣬�ļ�·�������Ժ��зǷ��ַ���ֻ��ʹ��ȫӢ��***
		***����definitions.h�и�������������ļ�·��***
	*/
	createGraphFromFile(FILE_PATH_FOR_INPUT);
	
	//������翪ʼʱ�� 
	int *beginningTime = getBeginningTime();
	
	//�������ʼʱ�� 
	int *endingTime = getEndingTime();
	
	//Ѱ�ҹؼ����� 
	int *criticalVertexes = findCriticalActivity(beginningTime, endingTime);
	
	//Ѱ�ҹؼ�·�����ؼ�� 
	vector<vector<int> > criticalPaths = findCriticalPath(criticalVertexes);
	
	//������ж�������������ʼʱ�� 
	writeForIntArr(beginningTime, 0, countOfVertexes, FILE_PATH_FOR_OUTPUT, "��ǰDAGͼÿ����������翪ʼʱ�䣬�����Ұ��ն����±�����");
	writeForIntArr(endingTime, 0, countOfVertexes, FILE_PATH_FOR_OUTPUT, "��ǰDAGͼÿ�����������ʼʱ�䣬�����Ұ��ն����±�����");
	
	//criticalVertexes�ĵ�һλ�ǹؼ�������������ӵڶ�λ��ʼ�Ƕ����±� 
	writeForIntArr(criticalVertexes, 1, criticalVertexes[0], FILE_PATH_FOR_OUTPUT, "��ǰDAGͼ�Ĺؼ����㣬�����Ұ��ն����±�����");
	//������йؼ�·�� 
	for(int i =0 ; i < criticalPaths.size() - 1; i++){
		if(i == 0){
			writeForVectorArr(criticalPaths[i], FILE_PATH_FOR_OUTPUT, "��ǰDAGͼ�Ĺؼ�·����");
		}else writeForVectorArr(criticalPaths[i], FILE_PATH_FOR_OUTPUT, "");
		
	}
	//������йؼ�� 
	writeForVectorArr(criticalPaths[criticalPaths.size() - 1], FILE_PATH_FOR_OUTPUT, "������л������ǰ����������̣����������Ǳ�(�)���±꣺");
	
	printf("\n\n����ɹ���");
	
	//��windows�Դ��ļ��±���д����ļ� 
	const char *command = NOTEPAD_OPEN_FILE_COMMAND;
	system(command);
	printf("\n\n");
	system("pause");
	return 0;
}
