#include <cstdio>
#include <cstdlib>

#define NOT_FOUND -1

typedef struct SLNode{
	char data;
	struct SLNode *next;
}SLNode;

//define the variable of length of two strings
int lengthOfMain = 0;
int lengthOfPattern = 0;

/*functions*/
//calculate the eigenvector of pattern string
int *next(char *pattern);

//calculate the length of string
int getArraySize(char *str);

//find the first index of matched string in the main string
int findIndexOfMatchedStr(char *main, char *pattern);

//create fuction, which can create char array from inputs
char *createCharArrayFromInputs(int *length);

//create single linked list for unknown length of input chars
SLNode *createLinkedListFromInput( int *length);

//convert function, which can create char array according to linked list
char *convertLinkedListToCharArray(SLNode *head, int length);
