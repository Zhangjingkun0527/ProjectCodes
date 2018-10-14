#include "headers.h"

//problem2
void jointTwoLinkedListsInversely(node *theJointedList, node *theOtherList){
	//first use the function f1 of problem1 to joint the two linked list
	jointTwoLinkedLists(theJointedList, theOtherList);
	
	//finally use the function f4 of problem4 to inverse the list processed by the function f1
	//then we will get the result.
	invertTheLinkedList(theJointedList);
}
