#include "definitions.h"

//ȥ�������еĻس��� 
void removeEnterSymbol(){
	char *c = (char *)malloc(sizeof(char));
	scanf("%c", c);
	free(c);
} 

