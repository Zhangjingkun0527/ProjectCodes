#include "headers.h"
//self-define some datas for testing the function
void testProblem1(){
	int data1[14] = {1, 2, 2, 2, 3, 4, 7, 8, 10, 13, 45, 50, 51, 100};
	node *group1 = (node *)malloc(sizeof(node));
	printf("Group1: ");
	generateListFromArray(group1, data1, 12);
	print(group1);
	printf("\n");
	
	int data2[11]  = {1, 2, 4, 10, 10, 10, 12, 20, 21, 29, 46};
	printf("Group2: ");
	node *group2 = (node *)malloc(sizeof(node));
	generateListFromArray(group2, data2, 11);
	print(group2);
	printf("\n");
	
	jointTwoLinkedLists(group1, group2);
	printf("Result: ");
	print(group1);
}

//problem1
void jointTwoLinkedLists(node *theJointedList, node *theOtherList){
	if (theJointedList->next == NULL) {
		theJointedList = theOtherList;
		return;
	}
	if (theOtherList->next == NULL) return;
	
	//define temporary pointer p, q, pre.
	//p and q indicate the current two pointer for comparation
	//pre indicates the current node of  the final linked list
	node *p = theJointedList->next, *q = theOtherList->next;
	node *pre = theJointedList;
	
	//when p and q is NULL, the while circulation should be shut down.
	//if p.data > q.data which means q will be added to the final linked list, 
	//so we should let pointer pre be q and q be the next node of q in order to next comparation, vice versa.
	
	while (p != NULL && q != NULL){
	 	if (p->data > q->data){
	 		pre->next = q;
	 		q = q->next;
		} else{
			pre->next = p;
		 	p = p->next;
		}
		 pre = pre->next;
	}
	
	//at last, if p or q is not NULL, indicating that there still exists some node after p or q
	//we should let it be the next node of pre.
	if (p != NULL){
		pre->next = p; 	
	}else if (q != NULL){
	 	pre->next = q;
	}
	
	//remove same data
	removeSameData(theJointedList);
}
