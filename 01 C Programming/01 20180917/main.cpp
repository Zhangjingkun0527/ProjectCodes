#include <iostream>
#include "Headers.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	/*problem 1 
	int **m1 = (int **)malloc(sizeof(int *) * 5);
	for(int i = 0; i < 5; i++){
		m1[i]= (int *)malloc(sizeof(int) * 8);
	}
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 8; j++){
			m1[i][j] = random(100);
		}	
	}
	
	int **m2 = (int **)malloc(sizeof(int *) * 8);
	for(int i = 0; i < 8; i++){
		m2[i]= (int *)malloc(sizeof(int) * 3);
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 3; j++){
			m2[i][j] = random(100);
		}	
	}
	
	int **r = (int **)malloc(sizeof(int *) * 5);
	for(int i = 0; i < 5; i++){
		r[i]= (int *)malloc(sizeof(int) * 3);
		for(int j = 0; j < 3; j++){
			r[i][j]=0;
		}
	}
	
	matrix_multiply(m1, m2, r, 5, 8, 3);
	*/
	
	/*Problem2
	char str[10] = {'a','g','e','A','v','T','V','k','E','Q'};
	proc(str);
	*/
	char str[20] = {'I','s',' ','P','A','T','&','T','A','P',' ','s','y','m','m','e','t','r','i','c'};
	findSymmetryChars(str);
	
	printf("\n\n");
	system("pause");
	return 0;
}
