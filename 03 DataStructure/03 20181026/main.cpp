#include "headers.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	//��ȡ����������� 
	BiTreeNode *root = getRootOfBinaryTreeFromInput();
	//���������� 
	printf("\n�ö�����������Ҷ���ֵ�ǣ�\n");
	outputAllLeaves(root, ONLY_PRINT);
	
	printf("\n�ö�������Ҷ�������ǣ�\n");
	int count = getNumOfLeaves(root);
	printf("%d", count);
	
	printf("\n\n");
	system("pause");
	return 0;
}
