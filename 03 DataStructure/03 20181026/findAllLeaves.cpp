#include "headers.h"
#include "Externs.h"

void printAllLeavesFromArray(char *arr){
	//calculate the size of btree array
	int sizeOfBtreeArray = pow(2, ceil(log(maxIndexOfBTree + 1) / log(2))) - 1;
	
	printf("The leaves of the binary trree you input are: \n");
	for(int i = 0; i <= maxIndexOfBTree; i++){
		if(arr[i] == '\n') continue;
		int leftChild = 2 * i + 1;
		int rightChild = leftChild + 1;
		bool doesLcExist = (leftChild < sizeOfBtreeArray) && (arr[leftChild] != '\n');
		bool doesRcExist = (rightChild < sizeOfBtreeArray) && (arr[rightChild] != '\n');
		if(!doesLcExist && !doesRcExist) printf("%c ", arr[i]);
	}
}

