#include "definitions.h"

//该函数将一个树根为输入的树转化为二叉树，并返回二叉树的根 
btNode *getBTreeRoot(tNode *tRoot){
	btNode *btRoot = (btNode *)malloc(sizeof(btNode));
	//给二叉树的根赋值 
	btRoot->data = tRoot->data; 
	btRoot->lchild = btRoot->rchild = NULL;
	converTreeToBTree(tRoot, btRoot);
	
	return btRoot;
} 

//该函数将一个树根为输入的数转化为对应的二叉树
void converTreeToBTree(tNode *tRoot, btNode *btRoot){
	//遇到叶子结点时返回 
	if(tRoot == NULL) return; 
	
	//首先为当前树结点的左孩子结点创建二叉树结点空间，如果为空，则其对应二叉树结点的左孩子置空 
	if(tRoot->lchild != NULL) {
		btNode *temp = (btNode *)malloc(sizeof(btNode));
		//将当前树结点的值赋给二叉树结点的值 
		temp->data = tRoot->lchild->data;
		//将二叉树结点的做后孩子暂时置空 
		temp->lchild = temp->rchild = NULL;
		//将当前树结点对应的二叉树结点的左孩子赋值，它等于其左孩子对应的二叉树结点值 
		btRoot->lchild = temp;
		
		//对当前树结点的左孩子进行相同的操作 
		converTreeToBTree(tRoot->lchild, btRoot->lchild);
		//释放掉创造的temp 
		//free(temp);
	}
	
	//最后为当前树结点的右兄弟结点创建二叉树结点空间，如果为空，则其对应二叉树结点的右孩子置空 
	if(tRoot->rBrother != NULL){
		btNode *temp = (btNode *)malloc(sizeof(btNode));
		//将当前树结点的值赋给二叉树结点的值 
		temp->data = tRoot->rBrother->data;
		//将二叉树结点的做后孩子暂时置空 
		temp->lchild = temp->rchild = NULL;
		//将当前树结点对应的二叉树结点的右孩子赋值，它等于其右兄弟对应的二叉树结点值 
		btRoot->rchild = temp;
		
		//对当前树结点的右兄弟进行相同的操作 
		converTreeToBTree(tRoot->rBrother, btRoot->rchild);
		//释放掉创造的temp 
		//free(temp);
	}
}
