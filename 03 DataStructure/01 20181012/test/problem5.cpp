#include "headers.h"

void  testProblem5(){
	int data[13] = {1, 3, 5, 7, 13, 19, 25, 43, 43, 51, 66, 70, 84};
	node *headNode  =(node *)malloc(sizeof(node));
	printf("Datas: ");
	generateListFromArray(headNode, data, 13);
	print(headNode);
	printf("\n");
	
	printf("Deleted(min:6, max: 50): ");
	deleteAllSpecifiedNodes(headNode, 6, 50);
	print(headNode);
}

//problem 5
void deleteAllSpecifiedNodes(node *list,  int i, int k){
	//if headNode has not next node, then do nothing
	if(list->next == NULL) return;
	
	node *p = list->next;
	//define two critical pointer to indicate the two critical nodes whose values are most closed to min and max.
	//define isFirstNodeFinded to indicate whether the first critical node is finded.
	node *criticalNode1 = list, *criticalNode2 = NULL;
	bool isFirstNodeFinded = false; 
	
	//in while circulation, we just need to find the two critical nodes.
	//for each node, if its value is equal to or smaller than min, in the same time
	//it has next node and the value of next node is larger than min, then the first critical node would be it.
	//likely, the second one is the node which has next node and the value is lager than max and whose value 
	//is equal to or larger than max.
	while(1) {
		if (p == NULL) break;
		if (!isFirstNodeFinded && p->next != NULL && p->next->data > i && p->data <= i){
			isFirstNodeFinded = true;
			criticalNode1 = p;
		}else if(p->next != NULL && p->next->data > k && p->data >= k){
			criticalNode2 = p;
			break;
		}
		
		p = p->next;
	}
	
	criticalNode1->next = criticalNode2;
}
