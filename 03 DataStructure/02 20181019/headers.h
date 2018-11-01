#include <cstdio>
#include <cstdlib>

#define FOUND 0
#define NOT_FOUND -1
#define NULL_EXCEPTION -2

//for string input
typedef struct SLNode{
	char data;
	struct SLNode *next;
}SLNode;

/*functions*/
//print the result
int printResult(char *str, int length);

//the funtion can find the maxlength and the first index of duplicate substring, then put them into an integer array
int *findIndexOfMatchedString(char *str, int length);

//create fuction, which can create char array from inputs
char *createCharArrayFromInputs(int *length);

//create single linked list for input chars which has unknown length
SLNode *createLinkedListFromInput( int *length);

//convert function, which can create char array according to linked list
char *convertLinkedListToCharArray(SLNode *head, int length);
