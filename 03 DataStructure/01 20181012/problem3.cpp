#include "headers.h"

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
