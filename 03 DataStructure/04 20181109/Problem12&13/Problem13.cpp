#include "definitions.h"

//定义该变量用于统计输入的森林的结点个数 
int countOfNodes = 0;
//定义该变量是用于主函数中nodeArr当前结点下标的指针，用于告诉当前添加到哪个位置了 
int indexOfNodeArr = 0;
//定义该一维数组，是为了记录每个结点在preNode中的位置 
int *indexOfRlink;

//该函数将得到的带度数的后序序列打印出来
void printDegreeNodes(){
	//先从console获取数据 
	varPreNode *head = getDatasFromConsole();
	
	//将获取到的数据转变为preNode数组 
	preNode **preNodeArr = convertCharArrToPreNodeArr(head);
	
	//获取每个结点的度数 
	int *degrees =  getDegreeFromPreNodeArr(preNodeArr);
	//根据结点数分配带度数的后序序列表示法的数组空间 
	degreeNode **nodeArr = (degreeNode **)malloc(sizeof(degreeNode *) * countOfNodes);
	//得到后序序列 
	getDegreeNodesFromPreNodeArr(preNodeArr, 0, degrees, nodeArr);
	
	//打印结果 
	printf("转换得到的后序序列及度数为：\n");
	for(int i = 0; i < countOfNodes; i++){
		printf("%c %d\n",nodeArr[i]->data, nodeArr[i]->degree);
	}
} 

/*
	主函数：递归获取后序序列存放至nodeArr中 
	参数说明：
		1、arr是带右链的先序序列表示法的结点数组
		2、index是arr的指针，指示每次递归时所处理是哪个arr的结点
		3、degreeArr是计算得到的每个结点的度数
		4、nodeArr是预先分配好的带度数的后序序列表示法的数组，在该函数中得到更改，最终结果也是存在它里面
		
	核心思想：
		本身带右链的先序序列就表示森林，通过操作ltag能直接知道每个结点的左孩子，rlink能知道右兄弟，因此可以利用这点直接进行
		后序遍历即可得到后序序列 
*/
void getDegreeNodesFromPreNodeArr(preNode **arr, int index, int *degreeArr, degreeNode **nodeArr){
	//对于处于indexOfArr的preNode结点，应当先考虑它是否有左孩子，如果没有则直接添加进入nodeArr
	//如果有左孩子，应当对它的左孩子进行同样处理 
	if(!arr[index]->ltag){
	 	//当有左孩子时，对左孩子进行同样处理，由于当前结点的左孩子就是紧挨着当前结点，因此index+1
		//这里不用考虑最后一个结点，因为先序序列的最后一个结点一定是叶结点。 
		getDegreeNodesFromPreNodeArr(arr, index + 1, degreeArr, nodeArr);
	}
	
	//当处理完结点nodeArr[index]左孩子情况时，它本身应当添加入后序序列中，处理类似于二叉树的中序序列
	visit(arr, index, degreeArr, nodeArr);
	
	//当处理完当前结点的左子树和其自身后，应当处理它的右兄弟 
	if(arr[index]->rlink != NULL){
		//当前结点的右链存在时，应当进行相同的处理
		//由于本函数是根据preNode的index来对每个结点进行跳跃处理，如果不用index那么将无法处理每个结点的左孩子
		//在输入函数部分，indexOfRlink按照每个结点的data值为索引记录了它们在preNode中的下标 
		getDegreeNodesFromPreNodeArr(arr, indexOfRlink[arr[index]->rlink->data - '#'], degreeArr, nodeArr);
	}    
	
}

//赋值函数，将index位置的preNode和degreeArr值赋给带度数的后序序列表示法数组nodeArr
void visit(preNode **arr, int index, int *degreeArr, degreeNode **nodeArr) {
	//如果没有左孩子，首先为nodeArr[indexOfNodeArr]分配空间 
	nodeArr[indexOfNodeArr] = (degreeNode *) malloc(sizeof(degreeNode));
	//给data赋值 
	nodeArr[indexOfNodeArr]->data = arr[index]->data;
	//给度数赋值 
	nodeArr[indexOfNodeArr]->degree = degreeArr[arr[index]->data - '#'];
	//nodeArr指针 自增1 
	indexOfNodeArr++;
}


//该函数可以统计带右链的先根次序表示法的森林中每个结点的度数，并以其ASCII值作为char数组下标返回 
int *getDegreeFromPreNodeArr(preNode **arr){
	//这里分配长度为92的数组用于方便使用哈希法给rlink赋值，因为输入时要求输入的字符只能是在35~126的ASCII字符 
	int *degreeArr = (int *)malloc(sizeof(int) * 92);
	
	//以下for循环统计每个结点的度数 
	preNode *p;
	int index = 0;
	int degree = 0;
	for(int i = 0; i < countOfNodes; i++){
		//每次统计，将index和degree置0 
		index = 0;
		degree = 0;
		
		//index是以当前结点arr[i]的值确定的哈希下标 
		index = arr[i]->data - '#';
		
		//如果结点arr[i]有左孩子，那么根据其左孩子的右链情况统计度数 
		//这里要考虑当前结点是不是最后一个结点，最后一个结点一定是叶结点，直接设置为0即可 
		if(!arr[i]->ltag && i != countOfNodes + 1){
			//如果arr[i]有左孩子，那么arr[i+1]一定是它的左孩子 
			p = arr[i + 1];
			//根据左孩子的右链情况统计度数 
			while(p) {
				degree++;
				p = p->rlink;
			}
		}
		degreeArr[index] = degree;
	}
	
	return degreeArr;
}


/* 以下是输入处理的3个函数，非算法主要部分 */

//该函数将convertVarPreNodesToCharArr()获取到的二维char数组转换为preNode数组
preNode **convertCharArrToPreNodeArr(varPreNode *head){
	//定义p指向链表表头的下一个结点，用于循环赋值 
	varPreNode *p = head->next;
	
	//分配preNode的指针数组 
	preNode **nodeArr = (preNode **)malloc(sizeof(preNode *) * countOfNodes);
	
	//这里分配长度为92的数组用于方便使用哈希法给rlink赋值，因为输入时要求输入的字符只能是在35~126的ASCII字符
	//由于对每个结点赋值时，实际上只是知道右链对应结点的data值并不清楚它的地址，这里将它们按照它们自己的data对应的下标存入
	//tempArr，这样给rlink赋值时，对于每个结点拿到rlink值就可以从tempArr中获取到地址 
	preNode **tempArr = (preNode **)malloc(sizeof(preNode *) * 92);
	
	//这里为文件头定义的indexOfRlink分配空间，这里主要是用于主函数中递归获取后序序列时对每个结点的rlink处理时方便获得rlink
	//在preNode数组中，因为preNode结点中rlink是指针，指向右兄弟结点，但是并不知道右兄弟结点在preNode中的位置，如果这里不记录
	//那么每次都要遍历preNode获取rlink的在preNode数组中的下标，不方便递归函数的建立。 
	//建立该数组后，我们可以通过preNode的data值从该数组中拿到它在preNode中的下标位置，这样每个结点的rlink的在
	//preNode中的下标也就能够拿到了，这是基于每个结点的值都不重复的假设前提 
	indexOfRlink = (int *)malloc(sizeof(int) * 92);
	
	//第一次循环先为每个结点创建结点空间，并设置ltag和data值
	int i = 0;
	
	while(p) {
		nodeArr[i]  = (preNode *)malloc(sizeof(preNode));
		//datas中的3位字符分别表示ltag data rlink值 
		nodeArr[i]->ltag = p->ltag; 
		nodeArr[i]->data = p->data;
		nodeArr[i]->rlink = NULL;
		
		//根据结点的值对应的哈希下标，存入tempArr中 
		int index = p->data - '#';
		tempArr[index] = nodeArr[i];
		
		//记录每个结点在preNode中的下标位置 
		indexOfRlink[index] = i;
		
		i++;
		p = p->next; 
	}
	
	//第二次循环为每个结点的rlink赋值，首先将i和p初始化 
	i = 0; 
	p = head->next;
	while(p){
		//如果当前结点没有右兄弟，则rlink置空 
		if(p->rlink == '!'){
			nodeArr[i]->rlink = NULL;
		}else{
			int index = p->rlink - '#';
			nodeArr[i]->rlink = tempArr[index];
			//这里对于每个结点记录它的右兄弟在 
			indexOfRlink[i] = index;	
		}
		
		i++;
		p = p->next;
	}
	
	free(tempArr);
	return nodeArr;
}


//从console获取用户输入的数据，并转换为可变长度链表存储 
varPreNode *getDatasFromConsole(){
	//创立头结点 
	varPreNode *head = (varPreNode *)malloc(sizeof(varPreNode));
	head->next = NULL;
	
	printf("请以“结点值 ltag 右兄弟结点值”的形式输入森林数据，例如“1 A B”，如果右指针无值，请输入英文叹号!表示无，例如“1 A !”。\n");
	printf("其中两个结点值只能是十进制值位于35~126的ASCII值，第33位是英文叹号!，第35位是#，第126位是~。\n");
	printf("最后结束请输入 “! 0 !”以表示输入完毕，这里要求每个结点的值不得重复！\n");
	varPreNode *p = head;
	while(1){
		char data;
		int ltag;
		char rlink;
		
		scanf("%c %d %c", &data, &ltag, &rlink);
		if(data == '!') break;
		
		//为结点赋值 
		varPreNode *temp = (varPreNode *)malloc(sizeof(varPreNode));
		temp->data = data;
		temp->ltag = ltag;
		temp->rlink = rlink;
		temp->next = NULL;
		
		//将p指向下一个，继续赋值 
		p->next = temp;
		p = p->next;
		
		//记录结点数目 
		countOfNodes++;
		
		//去除回车符 
		removeEnterSymbol();
	}
	
	return head;
}
