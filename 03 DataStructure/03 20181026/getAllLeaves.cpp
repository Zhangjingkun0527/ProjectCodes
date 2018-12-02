#include "headers.h"
//定义本文件的全局变量用于统计叶子结点数目 
int countOfLeaves = 0;
//该函数打印所有叶子结点的值 
void outputAllLeaves(BiTreeNode *root, int countOrPrint){
	if(root == NULL) return;
	//如果左右孩子都为空则打印结点值或不打印只计数 
	if(root->lchild == NULL && root->rchild == NULL && countOrPrint == ONLY_PRINT){
		printf("%c ", root->data);
	}else if(root->lchild == NULL && root->rchild == NULL && countOrPrint == ONLY_COUNT){
		countOfLeaves++;
	}
	
	outputAllLeaves(root->lchild, countOrPrint);
	outputAllLeaves(root->rchild, countOrPrint);
} 

//该函数获取所有叶子结点的个数 
int getNumOfLeaves(BiTreeNode *root){
	outputAllLeaves(root, ONLY_COUNT);
	return countOfLeaves; 
}
