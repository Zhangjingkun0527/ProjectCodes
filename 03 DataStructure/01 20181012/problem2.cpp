#include "headers.h"

void testProblem2(){
	int data1[13] = {1, 3, 5, 7, 13, 19, 25, 43, 43, 51, 66, 70, 84};
	node *group1 = (node *)malloc(sizeof(node));
	printf("Group1: ");
	generateListFromArray(group1, data1, 13);
	print(group1);
	printf("\n");
	
	int data2[10]  = {2, 4, 12, 20, 21, 29, 46, 50, 55, 72};
	printf("Group2: ");
	node *group2 = (node *)malloc(sizeof(node));
	generateListFromArray(group2, data2, 7);
	print(group2);
	printf("\n");
	
	jointTwoLinkedListsInversely(group1, group2);
	printf("Result: ");
	print(group1);
}

//problem2
void jointTwoLinkedListsInversely(node *theJointedList, node *theOtherList){
	//first use the function f1 of problem1 to joint the two linked list
	jointTwoLinkedLists(theJointedList, theOtherList);
	
	//finally use the function f4 of problem4 to inverse the list processed by the function f1
	//then we will get the result.
	invertTheLinkedList(theJointedList);
}
