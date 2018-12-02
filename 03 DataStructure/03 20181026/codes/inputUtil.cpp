#include "headers.h"
#include "Externs.h"

char * convertArrIntoBTreeArray(char *arr){
	if(arr == NULL) return NULL;
	
	//calculate the size of btree array
	int sizeOfBtreeArray = pow(2, ceil(log(maxIndexOfBTree + 1) / log(2))) - 1;
	char *btreeArr = (char *)malloc(sizeof(char) * sizeOfBtreeArray);
	for(int i = 0; i < sizeOfBtreeArray; i++)
		btreeArr[i] = '\n';
	
	for(int i = 0; i < sizeOfArrayFromInput; i++){
		btreeArr[indexesOfBTree[i]] = arr[i];
	}
	return btreeArr;
}

//this function is defined to create char array from input stream
char * convertInputToArray(){
	sizeOfArrayFromInput = printExample();
	if(sizeOfArrayFromInput == 0) return NULL;
	
	//for save indexes that are converted from chars and chars
	indexesOfBTree = (int *)malloc(sizeof(int) * sizeOfArrayFromInput);
	char *BTreeArray = (char *)malloc(sizeof(char) * sizeOfArrayFromInput);
	for(int i = 0; i < sizeOfArrayFromInput; i++){
		BTreeArray[i] = '\0';
	}
	
	int indexer = -1;
	//create binary tree from input stream
	for(int i = 0; i < sizeOfArrayFromInput; i++){
		char temp[10];
		for(int j = 0; j < 2; j++){
			scanf("%s", &temp);
			//first scanning for getting index whose length could be larger than 1
			bool legalResult = true;
			if(j == 0){
				if(!areAllCharsDigital(temp)){
					printf("The index you input must be digital!!Please reenter!!\n");
					legalResult = false;
					i--;
					continue;
				}
				
				int index = calculateIndex(temp, calculateSizeOfArray(temp));
				//if index is not legal, we should remind user to reenter
				legalResult = isIndexLegal(indexesOfBTree, sizeOfArrayFromInput, index, i == 0);
				if(legalResult){
					indexesOfBTree[++indexer] = index;
					if(i == sizeOfArrayFromInput - 1) 
						maxIndexOfBTree = index;
				}else{
					if(i == 0){
						printf("The binary tree must have a root node whose index must be 0!Please reenter!\n");
					}else{
						printf("The node you input is not legal!Because there is no father node in the nodes you've been input!Please reenter!\n");	
					}
					i--;
				}
			}else{
				//second scanning for getting the data of node, and the lengh of data can only be 1
				if(legalResult)	{
					BTreeArray[indexer] = temp[0];
				}
			}
			
		}
	}
	return BTreeArray;
}

//this function is defined to print example for inputing binary tree conveniently, 
//and return the amout of nodes in the binary tree
int printExample(){
	printf("Please input the amount of nodes, and press enter key for ending:\n");
	char temp[10];
	scanf("%s", &temp);
	
	while(c != ){
		printf("The amount must be larger than zero! Please reenter!\n");
		scanf("%d", &a);
	}
	
	printf("Please input each char data of the binary tree node, if there is no data for a node please just press enter:\n\n");
	printf("*****Note: you should input nodes like this:*****\n");
	printf("0 A\n");
	printf("5 D\n\n");
	printf("The first number indicates the index of node, which begins at 0, and after a space you should input the data.");
	printf("We could only support the char data! ***And the indexes must be in an ascending order!!***\n\n");
	
	return a;
}

//this function is define to calculate index according to the chars you input
int calculateIndex(char *indexArray, int size){
	if(!size) return -1;
	int index = 0;
	int temp = 0;
	for(int i = size - 1; i >= 0; i--){
		temp = indexArray[i] - '0';
		index += temp * pow(10, size - 1 - i);
	}
	return index;
}

//this function is defined to judge whether index you input is legal
bool isIndexLegal(int *indexes, int size, int index, bool isFirstIndex){
	if(isFirstIndex){
		return index == 0;
	}else{
		//check whether the index is legal, which means that we should check the node we input whether has a farther
		//which has been created already.
		bool isIndexLegal = false;
		for(int k = 0; k <= size; k++){
			if(indexes[k] * 2 + 1 == index || indexes[k] * 2 + 2 == index)
				isIndexLegal = true;
		}
		return 	isIndexLegal;
	} 
}

//this function is defined to calculate the length of char array from scanning
int calculateSizeOfArray(char *arr){
	int i = 0;
	char c = arr[i];
	while(c != '\0'){
		i++;
		c = arr[i];
	}
	return i;
}

//this function is defined to judge whether the index you input is digital
bool areAllCharsDigital(char *arr){
	bool result = true;
	int i = 0;
	char c = arr[i];
	while(c != '\0'){
		result &= c >= '0' && c <= '9';
		c = arr[++i];
	}
	return result;
}
