#include "definitions.h"

//去除最后输入的回车符
void removeEnterSymbol(){
	char *c = (char *)malloc(sizeof(char));
	scanf("%c", c);
	free(c);
} 
