#include <stdio.h>
#include <stdlib.h>

//define the node of single linked list
typedef struct node{
	struct node *next;
	int data;
}node;

//problem 1, make two non-decreasing single linked list jointed into a non-decreasing single linked list.
//the jointedList is the list which is regarded as return value, which means we would joint theOtherList into jointedList
//in the same time, jointedList and theOhterList are also params.
void jointTwoLinkedLists(node *theJointedList, node *theOtherList);
void testProblem1();

//problem2, which is highly similar with problem1.
void jointTwoLinkedListsInversely(node *theJointedList, node *theOtherList);
void testProblem2();

//problem3, find the node which owns the max value in a single Linked List, the return a pointer;
node * findMaxNode(node *headNode);
void testProblem3();

//prblem4, invert a single linked list.
void invertTheLinkedList(node *headNode);
void testProblem4();

//problem5, delete all nodes whose value is between param i and param k in a increasing linked list.
void deleteAllSpecifiedNodes(node *list,  int i, int k);
void testProblem5();

//problem 6, judge whether an input stream is a plalindrome 
void judgePlalindrome();
void testProblem6();

//print function for linked list
void print(node *list);

//according to the array set values for list.
//this function requires that list has been allocated memory
void generateListFromArray(node *list, int datas[], int size);

//this function can remove the surplus nodes which have same data from a non-decreasing linked list
void removeSameData(node *head);
