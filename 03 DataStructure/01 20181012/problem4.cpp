#include "headers.h"

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
