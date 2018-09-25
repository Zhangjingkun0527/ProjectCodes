#include "Headers.h"
void matrix_multiply(int **m1, int **m2, int **r, int x, int y, int z){
	
	printf ("Matrix m1:\n");
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			printf("%d ", m1[i][j]);
		}
		printf("\n");
	}
	
	printf ("\nMatrix m2:\n");
	for(int i = 0; i < y; i++){
		for(int j = 0; j < z; j++){
			printf("%d ", m2[i][j]);
		}
		printf("\n");
	}
	
	for(int i = 0; i < x; i++){
		for(int j = 0; j < z; j++){
			for(int k = 0; k < y; k++){
				r[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
	
	printf ("\nMatrix r:\n");
	for(int i = 0; i < x; i++){
		for(int j = 0; j < z; j++){
			printf("%d ", r[i][j]);
		}
		printf("\n");
	}
}
