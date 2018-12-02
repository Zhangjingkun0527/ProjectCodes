#include <cstdio>
#include <cstdlib>

//����������ĺ�������ʾ���Ľ��ṹ 
typedef struct degreeNode{
	char data;
	int degree;  //���� 
}degreeNode;

//��̬�������ֶ��������ʾ���Ľ��ṹ�嶨��
typedef struct tNode{
	char data; 
	struct tNode *lchild; //���� 
	struct tNode *rBrother; //���ֵ� 
}tNode;

//������������ȸ������ʾ�� 
typedef struct preNode{
	int ltag;
	char data;
	struct preNode *rlink;
}preNode;




/*
	Problem12 ����ض��壬���ｫ������ת��������������һ��ת����������ĿҪ��ĺ��� 
*/

//���ﶨ��ýṹ���ǿ��ǵ��޷���ǰ��֪����Ľ��������Ӷ���ȡ����ķ�ʽ�洢�����ת��Ϊ��ά���� 
typedef struct varDegreeNode{
	char data;
	int degree;
	struct varDegreeNode *next;
}varDegreeNode;

//�ú�������console����õ���άɭ������ת��Ϊ��̬�������ֱ�ʾ����ɭ�������ĸ����ָ����ɵ�һά���� 
tNode *getLinkedNode();

//�ú�������������ʽ�洢�Ĵ�������ʾ��ɭ������ת��Ϊ��̬�������ֱ�ʾ����ɭ�� 
tNode *convertDegreeNodeToLinkedNode(degreeNode **datas);

/* ���������봦���2�����������㷨��Ҫ���� */
//�ú�����console��ȡ������Դ������ĺ�������ʾ����ʾ��ɭ�����ݣ��������ά������ 
degreeNode **convertLinkedListToArr(varDegreeNode *head);

//�ú�����console��ȡ������Դ������ĺ�������ʾ����ʾ��ɭ�����ݣ������������ʽ�洢 
varDegreeNode *getDatasFromInput();


/*
	Problem13 ����ض��壬���ｫ������ת��������������һ��ת����������ĿҪ��ĺ��� 
*/

//���ﶨ��ýṹ���ǿ��ǵ��޷���ǰ��֪����Ľ��������Ӷ���ȡ����ķ�ʽ�洢�����ת��Ϊ��ά����  
typedef struct varPreNode{
	int ltag;
	char data;
	char rlink;
	struct varPreNode *next;
}varPreNode;

//�ú������õ��Ĵ������ĺ������д�ӡ������Ҳ��main�����е��õĺ��� 
void printDegreeNodes();

//�ú�������ǰ�����õ��Ķ����Լ�����õ���preNode����������õ��������ĺ�������ʾ�� 
void getDegreeNodesFromPreNodeArr(preNode **arr, int index, int *degreeArr, degreeNode **nodeArr);
									
//��ֵ��������indexλ�õ�preNode��degreeArrֵ����nodeArr
void visit(preNode **arr, int index, int *degreeArr, degreeNode **nodeArr);

//�ú�������ͳ�ƴ��������ȸ������ʾ����ɭ����ÿ�����Ķ�����������ASCIIֵ��Ϊint�����±귵�� 
int *getDegreeFromPreNodeArr(preNode **arr);


/* ���������봦���2�����������㷨��Ҫ���� */
//�ú�����convertVarPreNodesToCharArr()��ȡ���Ķ�άchar����ת��ΪpreNode����
preNode **convertCharArrToPreNodeArr(varPreNode *head);

/*
//�ú�����getDatasFromConsole()��ȡ��������ת��Ϊchar��ά�����ʾ 
char **convertVarPreNodesToCharArr(varPreNode *head);
*/

//��console��ȡ�û���������ݣ���ת��Ϊ�ɱ䳤������洢 
varPreNode *getDatasFromConsole();




/*
	TraverseUtil����ض��壬����ļ���Ҫ�Ƕ������������ֱ�ʾ��ɭ�ֵı�����������ڸ����ж��㷨��ȷ�� 
*/

//����ɭ�ֵ�ǰ����� 
void preOrder(tNode *root);

//����ɭ�ֵ�ǰ����� 
void postOrder(tNode *root);

//����ɭ�ֵ����и����ı��� 
void rightLink(tNode *root);



/*
	Util ��غ������� 
*/
//�ú�������ȥ���س��� 
void removeEnterSymbol(); 
