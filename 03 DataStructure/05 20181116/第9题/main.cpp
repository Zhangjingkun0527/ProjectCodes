#include "definitions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	printf("请先设置您所输入的图的类型，0代表无向图，1代表有向图：\n"); 
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
