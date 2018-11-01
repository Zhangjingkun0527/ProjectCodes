#include "headers.h"

void testProblem4(){
	int data[13] = {1, 13, 3, 19, 25, 5, 7, 51, 66, 43, 70, 84, 34};
	node *headNode  =(node *)malloc(sizeof(node));
	printf("Datas: ");
	generateListFromArray(headNode, data, 13);
	print(headNode);
	printf("\n");
	
	printf("Inverse: ");
	invertTheLinkedList(headNode);
	print(headNode);
}

//problem4
void invertTheLinkedList(node *headNode){
	//if headNode has not next node, then do nothing
	if(headNode->next == NULL) return;
	
	//define pre and p in which pre indicates the pre node of p and p incicate the current node
	node *pre = headNode->next;
	node *p = pre->next;
	pre->next = NULL;
	
	//when p is NULL, the list is traversed.
	//in each time, let node temp mark current the next node of p down, the let the next node p be pre, pre be p, p be temp
	node *temp;
	while(p != NULL){
		temp = p->next;
		p->next = pre;
		pre = p;
		p = temp;
	}
	
	headNode->next = pre;
}
