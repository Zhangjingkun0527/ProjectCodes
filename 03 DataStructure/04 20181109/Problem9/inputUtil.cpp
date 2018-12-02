#include "definitions.h"

//定义该变量是为了标记根结点的hash值 
int indexOfRoot = 0;

//该函数从input中获取树的结点数据并转换为动态左子右兄表示法，最后返回根结点
tNode *getTreeFromInput(){
	//获取由console得到的二维数组 
	char **datas = getInputDatas();
	//创建根结点 
	tNode *root = (tNode *)malloc(sizeof(tNode));
	root->lchild = root->rBrother = NULL;
	//创建动态左子右兄表示法的树 
	convertCharArrToNodeArr(datas, root, indexOfRoot);

	return root;
} 

//该函数递归的将输入所得的二维char数组转换为以静态链表表示的树的tNode数组，其中indexOfCharArr表示每次要操作datas行标 
void convertCharArrToNodeArr(char **datas, tNode *father, int indexOfCharArr){
	//当遇到datas某一行为空时就代表遇到了叶结点 
	if(datas[indexOfCharArr] == NULL) return;
	//对根结点的数据赋值 
	if(indexOfCharArr == indexOfRoot) father->data = datas[indexOfCharArr][0];
	
	//设置变量i用于记录当前datas行中的父结点子结点集长度 
	int i = 1; 
	//这里设置变量pre是为了记录当前结点的前一个兄弟结点并为其右兄弟结点赋值 
	tNode *pre = NULL; 
	//由于父结点已经被分配过空间，从而不需要再分配
	//这里为当前子结点集中的所有子结点分配空间，并递归为每个结点做同样的操作 
	for(char c = datas[indexOfCharArr][i]; c != '\0'; c = datas[indexOfCharArr][++i]){
		//对于每个子结点，为其分配空间，并对data赋值 
		tNode *child = (tNode *)malloc(sizeof(tNode));
		child->data = c;

		//左孩子、右兄弟指针暂时置空 
		child->lchild = child->rBrother = NULL;
		
		//给father的左孩子指针赋值，此时father结点内部数据赋值完毕 
		if(i == 1) father->lchild = child;
		
		//为当前子结点的前一个兄弟结点的右兄弟指针赋值 
		if(pre) pre->rBrother = child;
		
		//记录当前子结点的前一个兄弟结点，以便为给前一个兄弟结点的右兄弟结点赋值 
		pre = child;
		
		//对当前子结点的做同样的操作 
		convertCharArrToNodeArr(datas, child, c - 'A');
	}
} 

//该函数从console获取用户输入的单棵树的数据，并存储到二维char数组中返回 
char **getInputDatas(){
	printf("请输入树的根结点值，值只能是ASCII字符且只能是26个大写字母：\n");
	char c;
	scanf("%c", &c);
	indexOfRoot = c - 'A';
	
	printf("\n\n请以A-B-C-D-E的形式输入该树，其中A代表父结点，BCDE代表该父节点从左到右依次排序的孩子节点：\n");
	printf("最后结束请输入'#'，并回车\n");
	
	//定义二维数组，行数只有26列，因为要求的结点数据必须是大写字母
	char **datas = (char **)malloc(sizeof(char *) * 26);
	//对datas数组初始化 
	for(int i = 0; i < 26; i++)  datas[i] = NULL;
	
	//定义temp数组用于暂存输入的数据 
	char temp[20];
	while(1) {
		scanf("%s", temp);
		if(temp[0] == '#') break;
		
		//计算当前父结点子结点集的在二维char数组中所处位置 
		int index = temp[0] - 'A';
		if(datas[index] != NULL){
			printf("您已输入过该父节点及其所有子节点，请重新输入！\n");
			continue; 
		}
		
		//定义两个变量，lengthOfAll表示输入的字符串总长度，lengthOfNodes表示字符串中的结点数目 
		//统计当前输入的字符串长度 
		int lengthOfAll = 0, lengthOfNodes = 0;
		while(temp[lengthOfAll] != '\n'){
			if(temp[lengthOfAll] != '-') lengthOfNodes++;	
			lengthOfAll++; 
		} 
		
		//根据前面得到的结点数目，为对应父节点所在行分配空间，并将输入的结点赋值到对应位置 
		datas[index] = (char *)malloc(sizeof(char) * lengthOfNodes);
		for(int i = 0, j = 0; i < lengthOfAll; i++){
			if(temp[i] == '-') continue;
			datas[index][j++] = temp[i];
		}
	}
	
	return datas;
}
