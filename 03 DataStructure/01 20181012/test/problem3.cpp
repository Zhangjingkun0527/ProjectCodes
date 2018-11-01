#include "headers.h"

void testProblem3(){
	int data[13] = {1, 13, 3, 19, 25, 5, 7, 51, 66, 43, 70, 84, 34};
	node *headNode  =(node *)malloc(sizeof(node));
	printf("Datas: ");
	generateListFromArray(headNode, data, 13);
	print(headNode);
	printf("\n");
	
	node *result = findMaxNode(headNode);
	printf("Max: %d", result->data);
}

//problem3, this problem is very easy, so I'll not give any comments.
node * findMaxNode(node *headNode){
	//if headNode has not next node, then do nothing
	if(headNode->next == NULL) return headNode;
	
	node *p = headNode->next;
	node *result = p;
	while(p != NULL){
		if(p->data > result->data) result = p;
		p = p->next;
	}
	
	return result;
}
