#include "definitions.h"

//ȥ���������Ļس���
void removeEnterSymbol(){
	char *c = (char *)malloc(sizeof(char));
	scanf("%c", c);
	free(c);
} 
