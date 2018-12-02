#include "headers.h"
//���屾�ļ���ȫ�ֱ�������ͳ��Ҷ�ӽ����Ŀ 
int countOfLeaves = 0;
//�ú�����ӡ����Ҷ�ӽ���ֵ 
void outputAllLeaves(BiTreeNode *root, int countOrPrint){
	if(root == NULL) return;
	//������Һ��Ӷ�Ϊ�����ӡ���ֵ�򲻴�ӡֻ���� 
	if(root->lchild == NULL && root->rchild == NULL && countOrPrint == ONLY_PRINT){
		printf("%c ", root->data);
	}else if(root->lchild == NULL && root->rchild == NULL && countOrPrint == ONLY_COUNT){
		countOfLeaves++;
	}
	
	outputAllLeaves(root->lchild, countOrPrint);
	outputAllLeaves(root->rchild, countOrPrint);
} 

//�ú�����ȡ����Ҷ�ӽ��ĸ��� 
int getNumOfLeaves(BiTreeNode *root){
	outputAllLeaves(root, ONLY_COUNT);
	return countOfLeaves; 
}
