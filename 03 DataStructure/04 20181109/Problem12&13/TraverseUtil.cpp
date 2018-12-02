#include "definitions.h"

void preOrder(tNode *root){
	if(root == NULL) return;
	printf("%c ", root->data);
	preOrder(root->lchild);
	preOrder(root->rBrother);
}

void postOrder(tNode *root){
	if(root == NULL) return;
	postOrder(root->lchild);
	printf("%c ", root->data);
	postOrder(root->rBrother);	
}

void rightLink(tNode *root){
	if(root == NULL) return;
	printf("%c ", root->data);
	rightLink(root->rBrother);
}
