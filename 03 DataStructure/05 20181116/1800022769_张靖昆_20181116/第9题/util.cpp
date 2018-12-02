#include "definitions.h"

//去除输入中的回车符 
void removeEnterSymbol(){
	char *c = (char *)malloc(sizeof(char));
	scanf("%c", c);
	free(c);
} 

