#include <cstdio>
#include <cstdlib>

//动态左子右兄二叉链表表示法的结点结构体定义
typedef struct tNode{
	char data; 
	struct tNode *lchild; //左孩子 
	struct tNode *rBrother; //右兄弟 
}tNode;

//定义二叉树结点结构 
typedef struct btNode{
	char data;
	struct btNode *lchild;
	struct btNode *rchild;
}btNode;

/*
	convertTreeToBinaryTree的相关定义 
*/

//该函数将一个树根为输入的树转化为二叉树，并返回二叉树的根 
btNode *getBTreeRoot(tNode *tRoot);

//该函数递归地将一个树根为输入的树转化为对应的二叉树
void converTreeToBTree(tNode *tRoot, btNode *btRoot);



/*
	inputUtil的相关定义 
*/

//该函数从input中获取树的结点数据并转换为动态左子右兄表示法，最后返回根结点
tNode *getTreeFromInput();
 
//该函数递归的将输入所得的二维char数组转换为以静态链表表示的树的tNode数组，其中indexOfCharArr表示每次要操作datas行标 
void convertCharArrToNodeArr(char **datas, tNode *father, int indexOfCharArr); 

//该函数获取所输入的树的结点表示方法，并存入二维数组中
char **getInputDatas(); 
