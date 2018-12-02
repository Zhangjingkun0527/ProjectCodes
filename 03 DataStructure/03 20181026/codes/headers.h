#include <cstdio>
#include <cstdlib>
#include <cmath>

//define binary tree node
typedef struct BiTreeNode{
	char data;
	struct BiTreeNode *leftChild;
	struct BiTreeNode *rightChild;
}BiTreeNode;

/*
	findAllLeaves functions
*/
//this function is defined to print all leaves which are stored in an array
void printAllLeavesFromArray(char *arr);

//this function is defined to print all leaves which are stored in nodes
void printfAllLeavesFromNodes(BiTreeNode *root);


/*
	inputUtil functions
*/
//this function is defined to print example for inputing binary tree conveniently, 
//and return the amout of nodes in the binary tree
int printExample();

//this function is defined to convert char array into binary tree array
char * convertArrIntoBTreeArray(char *arr);

//this function is defined to create char array from input stream
char * convertInputToArray();

//this function is defined to judge whether index you input is legal
bool isIndexLegal(int *indexes, int size, int index, bool isFirstIndex);

//this function is defined to calculate index according to  the chars you input
int calculateIndex(char *indexArray, int size);

//this function is defined to calculate the length of char array from scanning
int calculateSizeOfArray(char *arr);

//this function is defined to judge whether the index you input is digital
bool areAllCharsDigital(char *arr);
