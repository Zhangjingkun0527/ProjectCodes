#include "definitions.h"

//�ú�����һ������Ϊ�������ת��Ϊ�������������ض������ĸ� 
btNode *getBTreeRoot(tNode *tRoot){
	btNode *btRoot = (btNode *)malloc(sizeof(btNode));
	//���������ĸ���ֵ 
	btRoot->data = tRoot->data; 
	btRoot->lchild = btRoot->rchild = NULL;
	converTreeToBTree(tRoot, btRoot);
	
	return btRoot;
} 

//�ú�����һ������Ϊ�������ת��Ϊ��Ӧ�Ķ�����
void converTreeToBTree(tNode *tRoot, btNode *btRoot){
	//����Ҷ�ӽ��ʱ���� 
	if(tRoot == NULL) return; 
	
	//����Ϊ��ǰ���������ӽ�㴴�����������ռ䣬���Ϊ�գ������Ӧ���������������ÿ� 
	if(tRoot->lchild != NULL) {
		btNode *temp = (btNode *)malloc(sizeof(btNode));
		//����ǰ������ֵ��������������ֵ 
		temp->data = tRoot->lchild->data;
		//��������������������ʱ�ÿ� 
		temp->lchild = temp->rchild = NULL;
		//����ǰ������Ӧ�Ķ������������Ӹ�ֵ�������������Ӷ�Ӧ�Ķ��������ֵ 
		btRoot->lchild = temp;
		
		//�Ե�ǰ���������ӽ�����ͬ�Ĳ��� 
		converTreeToBTree(tRoot->lchild, btRoot->lchild);
		//�ͷŵ������temp 
		//free(temp);
	}
	
	//���Ϊ��ǰ���������ֵܽ�㴴�����������ռ䣬���Ϊ�գ������Ӧ�����������Һ����ÿ� 
	if(tRoot->rBrother != NULL){
		btNode *temp = (btNode *)malloc(sizeof(btNode));
		//����ǰ������ֵ��������������ֵ 
		temp->data = tRoot->rBrother->data;
		//��������������������ʱ�ÿ� 
		temp->lchild = temp->rchild = NULL;
		//����ǰ������Ӧ�Ķ����������Һ��Ӹ�ֵ�������������ֵܶ�Ӧ�Ķ��������ֵ 
		btRoot->rchild = temp;
		
		//�Ե�ǰ���������ֵܽ�����ͬ�Ĳ��� 
		converTreeToBTree(tRoot->rBrother, btRoot->rchild);
		//�ͷŵ������temp 
		//free(temp);
	}
}
