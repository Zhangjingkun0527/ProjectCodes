#include "definitions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	printf("�����������������ͼ�����ͣ�0��������ͼ��1��������ͼ��\n"); 
	bool isDirectedGraph;
	scanf("%d", &isDirectedGraph);
	if(isDirectedGraph){
		findCircleOfDirectedGraph();
	}else{
		findCircleOfUndirectedGraph();
	}
	
	printf("\n\n");
	system("pause");
	return 0;
}
