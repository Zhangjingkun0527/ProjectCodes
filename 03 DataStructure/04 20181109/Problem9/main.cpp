#include "definitions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//���ﶨ��һ���������ĵݹ�������� 
void inOrder(btNode *root);
//���ﶨ��һ���������ĵݹ�ǰ����� 
void preOrder(btNode *root);

int main(int argc, char** argv) {
	tNode *tRoot = getTreeFromInput();
	btNode *btRoot = getBTreeRoot(tRoot);
	
	printf("\n\nת���õ���������ǰ������ǣ�\n");
	preOrder(btRoot);
	
	printf("\n\nת���õ�����������������ǣ�\n");
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
