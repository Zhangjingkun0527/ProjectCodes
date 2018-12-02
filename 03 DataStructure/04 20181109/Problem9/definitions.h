#include <cstdio>
#include <cstdlib>

//��̬�������ֶ��������ʾ���Ľ��ṹ�嶨��
typedef struct tNode{
	char data; 
	struct tNode *lchild; //���� 
	struct tNode *rBrother; //���ֵ� 
}tNode;

//������������ṹ 
typedef struct btNode{
	char data;
	struct btNode *lchild;
	struct btNode *rchild;
}btNode;

/*
	convertTreeToBinaryTree����ض��� 
*/

//�ú�����һ������Ϊ�������ת��Ϊ�������������ض������ĸ� 
btNode *getBTreeRoot(tNode *tRoot);

//�ú����ݹ�ؽ�һ������Ϊ�������ת��Ϊ��Ӧ�Ķ�����
void converTreeToBTree(tNode *tRoot, btNode *btRoot);



/*
	inputUtil����ض��� 
*/

//�ú�����input�л�ȡ���Ľ�����ݲ�ת��Ϊ��̬�������ֱ�ʾ������󷵻ظ����
tNode *getTreeFromInput();
 
//�ú����ݹ�Ľ��������õĶ�άchar����ת��Ϊ�Ծ�̬�����ʾ������tNode���飬����indexOfCharArr��ʾÿ��Ҫ����datas�б� 
void convertCharArrToNodeArr(char **datas, tNode *father, int indexOfCharArr); 

//�ú�����ȡ����������Ľ���ʾ�������������ά������
char **getInputDatas(); 
