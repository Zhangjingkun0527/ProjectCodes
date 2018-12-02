#include "headers.h"
#include "Global.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	char *temp = convertInputToArray();
	char *btree = convertArrIntoBTreeArray(temp);
	printAllLeavesFromArray(btree);
	printf("\n\n");
	system("pause");
	return 0;
}
