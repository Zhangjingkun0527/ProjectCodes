#include "definitions.h"

//定义该变量用于统计输入的森林的结点个数 
int numOfNodes = 0;

tNode *getLinkedNode(){
	//首先从console获取用户输入的带度数的后根表示法的森林数据，以链表形式存储 
	varDegreeNode *head = getDatasFromInput();
	
	//再次将上述链表转换为顺序存储结构 
	degreeNode **datas = convertLinkedListToArr(head);
	
	//最后将带度数的后根次序表示法的森林转换为动态左子右兄表示法的森林 
	return convertDegreeNodeToLinkedNode(datas);
}

//该函数将从console输入得到二维森林数据转换为动态左子右兄表示法的森林中树的根结点指针组成的一维数据 
tNode *convertDegreeNodeToLinkedNode(degreeNode **datas){
	//建立tNode栈，用于暂存已经分配空间但是没有建立左子右兄联系的结点 
	tNode **stack = (tNode **)malloc(sizeof(tNode *) * numOfNodes);
	int top = -1;
	for(int i = 0; i < numOfNodes; i++){
		//为当前结点分配左子右兄表示法结点的空间 
		tNode *temp = (tNode *)malloc(sizeof(tNode));
		temp->data = datas[i]->data;
		temp->lchild = temp->rBrother = NULL;
		
		//如果当前结点是叶节点，那么当前结点应当入栈
		if(datas[i]->degree == 0){
			++top;
			stack[top] = temp;
			continue; 
		}
		
		//以下对度数不为0的结点进行处理 
		if(datas[i]->degree == 1){ 
			//度数为1的结点，直接弹出栈顶的结点，这个结点就是这个度数为1结点的左孩子 
			temp->lchild = stack[top];
			top--;
		}else{
			//度数大于2的非叶结点建立子树结构，并将该子树的根结点压入栈中 
			int j = top;
			//建立pre指针用于给每个子结点的右兄弟指针赋值 
			tNode *pre = stack[top];
			top--;
			//建立p指针用于每个结点的操作
			tNode *p;
			//由于初始top与操作后的top相差值与degree相同时，代表当前结点的所有子结点都已操作结束 
			while(j - top != datas[i]->degree){
				//从栈顶拿出结点赋值给p，此时pre是p的右兄弟，应当对p的右兄弟指针赋值为pre 
				p = stack[top];
				top--;
				p->rBrother = pre;
				pre = p; 
			}
			//结束后，pre指向的就是左孩子，应当把当前结点temp左孩子指针指向pre 
			temp->lchild = p;
		}
	
		//非根结点应当压入栈中 
		++top;
		stack[top] = temp;
	}
	
	//当循环结束后，栈中剩余的结点就是所有树的根结点，我们将它连接到一起，表示整个森林
	tNode *tempRoot;
	for(int i = 0; i < top; i++){
		//显然前一棵树即第i棵树的右兄弟结点是后一棵树 
		stack[i]->rBrother = stack[i + 1];
	}
	
	//栈底的结点就是森林的根，也就是森林中第一棵树的根结点 
	return stack[0];
}



/* 以下是输入处理的2个函数，非算法主要部分 */

//该函数从console获取输入的以带度数的后根次序表示法表示的森林数据，并存入二维数组中 
degreeNode **convertLinkedListToArr(varDegreeNode *head){
	//如果没有输入结点，返回空 
	if(numOfNodes == 0)  return NULL;
	
	//分配degreeNode一维数组空间 
	degreeNode **datas = (degreeNode **)malloc(sizeof(degreeNode *) * numOfNodes);
	
	//开始对degreeNode一维数组的每个结点进行赋值 
	varDegreeNode *p = head->next, *temp;
	//degreeNode一维数组下标 
	int i = 0;
	while(p){
		//为每个结点赋值 
		datas[i] = (degreeNode *)malloc(sizeof(degreeNode));
		datas[i]->data = p->data;
		datas[i]->degree = p->degree;
		
		//对于使用过的varDegreeNode结点应当释放掉 
		temp = p;
		p = p->next;
		free(temp);
		
		i++;
	}
	
	return datas; 
}

//该函数从console获取输入的以带度数的后根次序表示法表示的森林数据，并以链表的形式存储 
varDegreeNode *getDatasFromInput(){
	//创立头结点 
	varDegreeNode *head = (varDegreeNode *)malloc(sizeof(varDegreeNode));
	head->next = NULL;
	
	printf("请以“结点值 度数”的形式输入森林数据，最后结束请输入“# -1”以表示输入完毕：\n");
	varDegreeNode *p = head;
	while(1){
		char data;
		int degree;
		scanf("%c %d", &data, &degree);
		if(data == '#') break;
		
		//为结点赋值 
		varDegreeNode *temp = (varDegreeNode *)malloc(sizeof(varDegreeNode));
		temp->data = data;
		temp->degree = degree;
		temp->next = NULL;
		
		//将p指向下一个，继续赋值 
		p->next = temp;
		p = p->next;
		
		//记录结点数目 
		numOfNodes++;
		
		//去除最后输入的回车符
		removeEnterSymbol();
	}
	
	return head;
} 
