#include "headers.h" 
//定义该文件内的全局变量，用于记录根结点的下标 
int indexOfRoot = -1;

//该函数返回根据输入创建的二叉树根结点指针 
BiTreeNode *getRootOfBinaryTreeFromInput(){
	char **datas = getInputData();
	BiTreeNode *root;
	root = convertCharArrayIntoBiTreeNode(datas, NULL, indexOfRoot);
	return root;
}

//根据数组递归创建二叉树 
BiTreeNode *convertCharArrayIntoBiTreeNode(char **datas, BiTreeNode *root, int index){
	//当递归查询遇到叶节点时，则返回NULL 
	if(datas[index][0] == '\n') return NULL;
	
	//非叶节点，首先给root分配空间 
	root = (BiTreeNode *)malloc(sizeof(BiTreeNode));

	//非叶节点的值为datas数组中对应下标父结点值
	root->data = datas[index][0];
	root->lchild = NULL;
	root->rchild = NULL;
	
	//为左孩子赋值 
	BiTreeNode *templ = convertCharArrayIntoBiTreeNode(datas, root->lchild, datas[index][1]);
	//如果templ是NULL，则说明左孩子是叶子结点，直接为其赋值 
	if(templ == NULL && datas[index][1] != '\n'){
		root->lchild = (BiTreeNode *)malloc(sizeof(BiTreeNode));
		root->lchild->data = datas[index][1];
		root->lchild->lchild = NULL;
		root->lchild->rchild = NULL;
	}else root->lchild = templ;
	
	//为右孩子赋值 
	BiTreeNode *tempr = convertCharArrayIntoBiTreeNode(datas, root->rchild, datas[index][2]);
	//如果tempr是NULL，则说明右孩子是叶子结点，直接为其赋值 
	if(tempr == NULL && datas[index][2] != '\n'){
		root->rchild = (BiTreeNode *)malloc(sizeof(BiTreeNode));
		root->rchild->data = datas[index][2];
		root->rchild->lchild = NULL;
		root->rchild->rchild = NULL;
	}else root->rchild = tempr;
	
	return root;
} 

//定义输入函数，从console端获取输入的二叉树数据，以A-B-L形式表示父节点-子节点-左孩子，返回拆分过后的BiTreeNode二维数组
//由于提前认定二叉树结点中的data值只能为Char，从而可以用哈希表来做 ，长度给定256个ASCII字符 
char **getInputData(){
	//用二维数组存储所有的值 
	char **datas = (char **)malloc(sizeof(char *) * 256);
	for(int i = 0; i < 256; i++){
		//每行存储3个值即根结点值(0)、左孩子节点值(1)、右孩子结点值(2)，全部初始化为'\n' 
		datas[i]  = (char *)malloc(sizeof(char) * 4);
		datas[i][0] = datas[i][1] = datas[i][2] = '\n';
	}
	
	//首先设置根节点 
	printf("请先输入根结点的值，值只能是ACSII字符：\n");
	char root;
	scanf("%c", &root);
	indexOfRoot = root;
	
	printf("\n\n");
	printf("请输入二叉树的所有结点关系，以A-B-L形式输入，其中A表示父节点值，B表示孩子结点值，L表示左右孩子结点的标记。\n\n");
	printf("***若父节点是二叉树根结点，请以A-B-L-t或A-B-L-T单独标识。最终的结尾以单个符号'#'结束：***\n\n");

	
	//定义临时数组用于暂存输入的数据
	char temp[8];
	int index = 0;
	while(1) {
		scanf("%s", temp);
		
		//遇到单个符号'#'时终止输入 
		if(temp[0] == '#')  break;
		
		//将父节点的值作为哈希数组下标 
		index = temp[0];
		
		//判断当前结点是否为父节点，如果是则给indexOfRoot赋值 
		if((temp[6] == 'T' || temp[6] == 't') && indexOfRoot != -1){
			indexOfRoot = index;
		}
		
		//定义该变量是为了简化代码 
		bool isLeftChild = temp[4] == 'L' || temp[4] == 'l';
		datas[index][0] = temp[0];
		if(temp[4] == 'L' && datas[index][1] == '\n'){
			datas[index][1] = temp[2];
			continue;
		}else if(temp[4] == 'L' && datas[index][1] != '\n'){
			//当输入的结点对已经存在时，判断是否要覆盖 
			printf("根结点为%c的左孩子结点已经存在，值为%c，是否覆盖，是输入1，反之输入0：\n", temp[4], datas[index][1]);
			char c;
			scanf("%c", &c);
			if(c == '1'){
				datas[index][1] = temp[2];
			}
			continue;
		}
		
		bool isRightChild = temp[4] == 'R' || temp[4] == 'r';
		if(isRightChild && datas[index][2] == '\n'){
			datas[index][2] = temp[2];
			continue;
		}else if(isRightChild && datas[index][2] != '\n'){
			//当输入的结点对已经存在时，判断是否要覆盖 
			printf("根结点为%c的左孩子结点已经存在，值为%c，是否覆盖，是输入1，反之输入0：\n", temp[4], datas[index][1]);
			char c;
			scanf("%c", &c);
			if(c == '1'){
				datas[index][2] = temp[2];
			}
			continue;
		}
	} 
	
	return datas; 
}
