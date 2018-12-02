#include <cstdio>
#include <cstdlib>

#ifndef ONLY_COUNT
#define ONLY_COUNT 1
#endif

#ifndef ONLY_PRINT
#define ONLY_PRINT 2
#endif

//定义二叉树结点的结构体 
typedef struct BiTreeNode{
	char data; //结点值
	struct BiTreeNode *lchild; //左孩子结点
	struct BiTreeNode *rchild; //右孩子结点
}BiTreeNode; 



/*
    getAllLeaves的相关函数定义 
*/

//该函数打印所有叶子结点的值 
void outputAllLeaves(BiTreeNode *root, int countOrPrint);

//该函数获取所有叶子结点的个数 
int getNumOfLeaves(BiTreeNode *root);


/*
	inputUtil的相关函数定义 
*/

//该函数返回根据输入创建的二叉树根结点指针 
BiTreeNode *getRootOfBinaryTreeFromInput();

//该函数将存储二叉树值的二维数组转化为二叉树结构
BiTreeNode *convertCharArrayIntoBiTreeNode(char **datas, BiTreeNode *root, int index);

//定义输入函数，从console端获取输入的二叉树数据，以A-B-L形式表示父节点-子节点-左孩子，返回拆分过后的BiTreeNode二维数组
char **getInputData();
