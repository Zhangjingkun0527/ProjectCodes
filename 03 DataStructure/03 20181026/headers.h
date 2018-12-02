#include <cstdio>
#include <cstdlib>

#ifndef ONLY_COUNT
#define ONLY_COUNT 1
#endif

#ifndef ONLY_PRINT
#define ONLY_PRINT 2
#endif

//������������Ľṹ�� 
typedef struct BiTreeNode{
	char data; //���ֵ
	struct BiTreeNode *lchild; //���ӽ��
	struct BiTreeNode *rchild; //�Һ��ӽ��
}BiTreeNode; 



/*
    getAllLeaves����غ������� 
*/

//�ú�����ӡ����Ҷ�ӽ���ֵ 
void outputAllLeaves(BiTreeNode *root, int countOrPrint);

//�ú�����ȡ����Ҷ�ӽ��ĸ��� 
int getNumOfLeaves(BiTreeNode *root);


/*
	inputUtil����غ������� 
*/

//�ú������ظ������봴���Ķ����������ָ�� 
BiTreeNode *getRootOfBinaryTreeFromInput();

//�ú������洢������ֵ�Ķ�ά����ת��Ϊ�������ṹ
BiTreeNode *convertCharArrayIntoBiTreeNode(char **datas, BiTreeNode *root, int index);

//�������뺯������console�˻�ȡ����Ķ��������ݣ���A-B-L��ʽ��ʾ���ڵ�-�ӽڵ�-���ӣ����ز�ֹ����BiTreeNode��ά����
char **getInputData();
