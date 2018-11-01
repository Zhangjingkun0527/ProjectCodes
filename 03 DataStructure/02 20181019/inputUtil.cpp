#include "headers.h"

//create fuction, which can create char array from inputs
char *createCharArrayFromInputs(int *length){
	SLNode *head = createLinkedListFromInput(length);
	if(head->next == NULL) return NULL;
	return convertLinkedListToCharArray(head, *length);
}

//create single linked list for unknown length of input chars
char *convertLinkedListToCharArray(SLNode *head, int length){
	char *array = (char *)malloc(sizeof(char) * length);
	int i = -1;
	while (head){
		SLNode *p;
		p = head;
		head = head->next;
		if(head)
			array[++i] = head->data; 
		
		delete p;
	}
	
	return array;
}

//create single linked list for unknown length of input chars
SLNode *createLinkedListFromInput(int *length){
	char c;
	SLNode * head = (SLNode *)malloc(sizeof(SLNode));
	SLNode * p = (SLNode *)malloc(sizeof(SLNode));
	head->next = p;
	
	while(1){
		c = getchar();
		if (c == '\n') {
			p->next = NULL;
			break;
		}
		(*length)++;
		p->data = c;
		p->next = (SLNode *)malloc(sizeof(SLNode));
		p = p->next;
	}
	
	return head;
}
