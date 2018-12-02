#include <cstdio>
#include <cstdlib>

//定义带度数的后根次序表示法的结点结构 
typedef struct degreeNode{
	char data;
	int degree;  //度数 
}degreeNode;

//动态左子右兄二叉链表表示法的结点结构体定义
typedef struct tNode{
	char data; 
	struct tNode *lchild; //左孩子 
	struct tNode *rBrother; //右兄弟 
}tNode;

//定义带右链的先根次序表示法 
typedef struct preNode{
	int ltag;
	char data;
	struct preNode *rlink;
}preNode;




/*
	Problem12 的相关定义，这里将输入与转换函数都放在了一起，转换函数是题目要求的核心 
*/

//这里定义该结构体是考虑到无法提前得知输入的结点个数，从而采取链表的方式存储，最后转化为二维数组 
typedef struct varDegreeNode{
	char data;
	int degree;
	struct varDegreeNode *next;
}varDegreeNode;

//该函数将从console输入得到二维森林数据转换为动态左子右兄表示法的森林中树的根结点指针组成的一维数据 
tNode *getLinkedNode();

//该函数将以链表形式存储的带度数表示法森林数据转换为动态左子右兄表示法的森林 
tNode *convertDegreeNodeToLinkedNode(degreeNode **datas);

/* 以下是输入处理的2个函数，非算法主要部分 */
//该函数从console获取输入的以带度数的后根次序表示法表示的森林数据，并存入二维数组中 
degreeNode **convertLinkedListToArr(varDegreeNode *head);

//该函数从console获取输入的以带度数的后根次序表示法表示的森林数据，并以链表的形式存储 
varDegreeNode *getDatasFromInput();


/*
	Problem13 的相关定义，这里将输入与转换函数都放在了一起，转换函数是题目要求的核心 
*/

//这里定义该结构体是考虑到无法提前得知输入的结点个数，从而采取链表的方式存储，最后转化为二维数组  
typedef struct varPreNode{
	int ltag;
	char data;
	char rlink;
	struct varPreNode *next;
}varPreNode;

//该函数将得到的带度数的后序序列打印出来，也是main函数中调用的函数 
void printDegreeNodes();

//该函数根据前面计算得到的度数以及输入得到的preNode，经过处理得到带度数的后根次序表示法 
void getDegreeNodesFromPreNodeArr(preNode **arr, int index, int *degreeArr, degreeNode **nodeArr);
									
//赋值函数，将index位置的preNode和degreeArr值赋给nodeArr
void visit(preNode **arr, int index, int *degreeArr, degreeNode **nodeArr);

//该函数可以统计带右链的先根次序表示法的森林中每个结点的度数，并以其ASCII值作为int数组下标返回 
int *getDegreeFromPreNodeArr(preNode **arr);


/* 以下是输入处理的2个函数，非算法主要部分 */
//该函数将convertVarPreNodesToCharArr()获取到的二维char数组转换为preNode数组
preNode **convertCharArrToPreNodeArr(varPreNode *head);

/*
//该函数将getDatasFromConsole()获取到的链表转换为char二维数组表示 
char **convertVarPreNodesToCharArr(varPreNode *head);
*/

//从console获取用户输入的数据，并转换为可变长度链表存储 
varPreNode *getDatasFromConsole();




/*
	TraverseUtil的相关定义，这个文件主要是定义了左子右兄表示法森林的遍历结果，用于辅助判断算法正确性 
*/

//定义森林的前序遍历 
void preOrder(tNode *root);

//定义森林的前序遍历 
void postOrder(tNode *root);

//定义森林的所有根结点的遍历 
void rightLink(tNode *root);



/*
	Util 相关函数定义 
*/
//该函数用于去除回车符 
void removeEnterSymbol(); 
