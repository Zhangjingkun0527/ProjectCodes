#include "definitions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//这里定义一个二叉树的递归中序遍历 
void inOrder(btNode *root);
//这里定义一个二叉树的递归前序遍历 
void preOrder(btNode *root);

int main(int argc, char** argv) {
	tNode *tRoot = getTreeFromInput();
	btNode *btRoot = getBTreeRoot(tRoot);
	
	printf("\n\n转换得到二叉树的前序遍历是：\n");
	preOrder(btRoot);
	
	printf("\n\n转换得到二叉树的中序遍历是：\n");
	inOrder(btRoot);
	
	printf("\n\n");
	system("pause");
	return 0;
}

void inOrder(btNode *root){
	if(root == NULL) return;
	inOrder(root->lchild);
	printf("%c ", root->data);
	inOrder(root->rchild);
}

void preOrder(btNode *root){
	if(root == NULL) return;
	printf("%c ", root->data);
	preOrder(root->lchild);
	preOrder(root->rchild);
}
