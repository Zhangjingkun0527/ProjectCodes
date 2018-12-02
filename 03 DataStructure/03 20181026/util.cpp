#include "headers.h"

//该函数实现结点node2的值拷贝到node1的值
void btNodeCopy(BiTreeNode *node1, BiTreeNode *node2){
	if(node2 == NULL) node1 = NULL;
	node1->data = node2->data;
	node1->lchild = node2->lchild;
	node1->rchild = node2->rchild;
}
