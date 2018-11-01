#include "headers.h"

int printResult(char *str, int length){
	int *result = findIndexOfMatchedString(str, length);
	if(result == NULL) return NULL_EXCEPTION;
	if(result[0] == 0) return NOT_FOUND;
	printf("Congratulations! We have found the matched substring!^_^\n");
	printf("The maximum of duplicate substring is %d:\n\n", result[0]);
	printf("The first index of duplicate substring is %d:\n\n", result[1]);
	printf("The duplicate substring which has maximum length is: ");
	for(int i = result[1]; i < result[0] + result[1]; i++){
		printf("%c", str[i]);
	}
	return FOUND;
}

// logic: let us use an exmple to illustrate this function clearly
// first step
// index: 0 1 2 3 4 5 6 7 8
// str1:  a b c d a c d a c
// str2:    a b c d a c d a c
// .....
// index: 0 1 2 3 4 5 6 7 8
// str1:  a b c d a c d a c
// str2:        a b c d a c d a c
// until this step, we can find that between index 5 - index 8, the substring is same.
// what we need to do is that, in each step, record the maxLength and first index if a continuous chars are the same, 
// finally, find the  maximum maxLength, then we get the result.
int *findIndexOfMatchedString(char *str, int length){
	if(str == NULL) return NULL;
	
	int i = 0, j = 0, k = 1;
	int maxLength = 0, index = 0;
	while(k < length){
		i = k;
		j = 0;
		int tempLength = 0;
		int tempIndex = 0;
		bool hasIndexAssigned = false;
		for(; i < length; i++, j++){
			if(str[i] == str[j]){
				tempLength++;
				if(!hasIndexAssigned) {
					tempIndex = j;
					hasIndexAssigned = true;
				}
			}else{
				if(tempLength > maxLength){
					maxLength = tempLength;
					index = tempIndex;
				}
				tempLength = 0;
				tempIndex = 0;
				hasIndexAssigned = false;
			}
		}
		if(tempLength > maxLength){
			maxLength = tempLength;
			index = tempIndex;
		}
		k++;
	}
	
	int result[2] = {maxLength, index};
	return result;
}
