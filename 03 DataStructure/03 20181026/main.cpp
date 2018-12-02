#include "headers.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	//获取二叉树根结点 
	BiTreeNode *root = getRootOfBinaryTreeFromInput();
	//仅输出根结点 
	printf("\n该二叉树的所有叶结点值是：\n");
	outputAllLeaves(root, ONLY_PRINT);
	
	printf("\n该二叉树的叶结点个数是：\n");
	int count = getNumOfLeaves(root);
	printf("%d", count);
	
	printf("\n\n");
	system("pause");
	return 0;
}
