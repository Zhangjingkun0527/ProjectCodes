#include "headers.h"

void testProblem6(){
	judgePlalindrome();
}

//problem6
void judgePlalindrome(){
	//define a stack array with an exact size 10w which suppossed that the number of char before '&' would not surpass 10w
	char stack[100000];
	int top = -1;
	
	printf("Please input the string, then press the enter key and end the string with '#': \n");
	//define char variable c for input and bool variable for judging whether character '&' has came out ever.
	char c;
	bool hasAndSymbolCameOut = false;
	while (1){
		c = getchar();
		//if c is equal to '#', then break the circulation
		if (c == '#') break;
		//if c is equal to '&', then set hasAndSymbolCameOut true
		if (c == '&') {
			hasAndSymbolCameOut =  true;
			continue;
		}
		//if hasAndSymbolCameOut is true, then we need to judge, for each char in the stack, 
		//whether the corresponding character is same as it. if not, printf the negative answer and close the function.
		//or, we need to push char into the stack.
		if (hasAndSymbolCameOut){
			if (top == -1 || stack[top--] != c){
				printf("This is not a Plalindrome!\n");
				return;
			}
		} else{
			stack[++top] = c;
		}
	}
	
	if(!hasAndSymbolCameOut) {
		printf("Please do not forget split symbol '&'!!\n\n");
		return;
	}
	//if while circulation is over, that indicates that the string is a Plalindrome.
	printf("This is a Plalindrome!\n");
}
