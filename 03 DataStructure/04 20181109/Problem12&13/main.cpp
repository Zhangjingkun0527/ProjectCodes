#include "definitions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	
	printf("请输入0或1选择问题，0表示问题12，1表示问题13：\n");
	int choice;
	scanf("%d", &choice);
	removeEnterSymbol();
	if(!choice){
		printf("******************问题12********************\n");
		tNode *root = getLinkedNode();
		printf("\n\n转换得到的左子右兄表示法的树的前序遍历是：\n");
		preOrder(root);
		
		printf("\n\n转换得到的左子右兄表示法的树的后序遍历是：\n");
		postOrder(root);
		
		printf("\n\n转换得到的左子右兄表示法的树的所有右链即森林中每棵树的根结点是：\n");
		rightLink(root);	
	}else{
		printf("******************问题13********************\n");
		printDegreeNodes();
	}
	
	printf("\n\n");
	system("pause");
	return 0;
}


