#include "headers.h"

//The entrance of program
int main(int argc, char** argv) {
	//create main string from inputs
	printf("Please enter the string and press enter for ending:\n");
	int length = 0;
	char *str = createCharArrayFromInputs(&length);
	int result = printResult(str, length);
	if (result == NOT_FOUND){
		printf("Sorry! There is no duplicate substring in the string you input!^_^\n");
	} else if(result == NULL_EXCEPTION){
		printf("Sorry! There is something wrong about program, please contact the author!\n");
	}
	
	printf("\n\n");
	system("pause");
	return 0;
}
