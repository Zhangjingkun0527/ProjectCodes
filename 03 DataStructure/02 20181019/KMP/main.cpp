#include "headers.h"


//The entrance of program
int main(int argc, char** argv) {
	//create main string from inputs
	/*
	printf("Please enter the Main string and press enter for ending:\n");
	char * main = createCharArrayFromInputs(&lengthOfMain);
	while (!main){
		printf("The string can not be empty!Please input again:\n");
		main = createCharArrayFromInputs(&lengthOfMain);	
	}
	printf("\n");
	*/
	//create pattern string from inputs
	printf("Please enter the Pattern string and press enter for ending:\n");
	char *pattern = createCharArrayFromInputs(&lengthOfPattern);
	while (!pattern){
		printf("The string can not be empty! Please input again:\n");
		pattern = createCharArrayFromInputs(&lengthOfPattern);	
	}
	printf("\n");
	
	int *a = next(pattern);
	for(int i = 0; i < lengthOfPattern; i++){
		printf("%d ", a[i]);
	}
	/*
	//output the result
	int index = findIndexOfMatchedStr(main, pattern);
	if (index != NOT_FOUND){
		printf("Congratulations! The begging index of matched string in the main string is %d!\n", index);
	} else{
		printf("There is no matched string in the main string as to pattern string!\n");
	}
	*/
	system("pause");
	return 0;
}

//main processing function of KMP algorithm
int findIndexOfMatchedStr(char *main, char *pattern){
	
	//main logic
	int *nextVal = next(pattern);
	int j = 0, k = 0;
	while (j < lengthOfMain){
		if (k == -1 || main[j] == pattern[k]){
			k++;
		} else if(k < lengthOfPattern){
			k = nextVal[k];
		} else return j - k;
		j++;
	}
	
	return NOT_FOUND;
}

//this function could calculate the eigenvector of pattern string
//and this function is the improvement of KMP algorithm, which will not get better answer
//if it processes the string like 'aaaaabb' that has many continuous and same chars.
/*
main      a  c
index     0  1  2  3  4  5  6  7  8  9
String    a  b  c  d  a  a  b  c  a  b
nextV  	 -1  0  i k
*/
int *next(char *pattern){
	if(!lengthOfPattern) return NULL;
	
	int *nextVal = (int *)malloc(sizeof(int) * lengthOfPattern);
	int j = 0;
	int k = -1;
	nextVal[0] = -1;
	
	while(j < lengthOfPattern){
		if(k == -1 || pattern[k] == pattern[j]){
			++j;
			++k;
			nextVal[j] = k;
			/*
			if(pattern[j] != pattern[k]){
				nextVal[j] = k;
			} else{
				nextVal[j]	= nextVal[k];
			}*/
		} else{
			k = nextVal[k];
		}
	}
	
	return nextVal;
}

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
