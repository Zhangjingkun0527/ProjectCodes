#include "definitions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	
	printf("������0��1ѡ�����⣬0��ʾ����12��1��ʾ����13��\n");
	int choice;
	scanf("%d", &choice);
	removeEnterSymbol();
	if(!choice){
		printf("******************����12********************\n");
		tNode *root = getLinkedNode();
		printf("\n\nת���õ����������ֱ�ʾ��������ǰ������ǣ�\n");
		preOrder(root);
		
		printf("\n\nת���õ����������ֱ�ʾ�������ĺ�������ǣ�\n");
		postOrder(root);
		
		printf("\n\nת���õ����������ֱ�ʾ������������������ɭ����ÿ�����ĸ�����ǣ�\n");
		rightLink(root);	
	}else{
		printf("******************����13********************\n");
		printDegreeNodes();
	}
	
	printf("\n\n");
	system("pause");
	return 0;
}


