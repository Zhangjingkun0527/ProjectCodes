#include "definitions.h"

//����ñ�����Ϊ�˱�Ǹ�����hashֵ 
int indexOfRoot = 0;

//�ú�����input�л�ȡ���Ľ�����ݲ�ת��Ϊ��̬�������ֱ�ʾ������󷵻ظ����
tNode *getTreeFromInput(){
	//��ȡ��console�õ��Ķ�ά���� 
	char **datas = getInputDatas();
	//��������� 
	tNode *root = (tNode *)malloc(sizeof(tNode));
	root->lchild = root->rBrother = NULL;
	//������̬�������ֱ�ʾ������ 
	convertCharArrToNodeArr(datas, root, indexOfRoot);

	return root;
} 

//�ú����ݹ�Ľ��������õĶ�άchar����ת��Ϊ�Ծ�̬�����ʾ������tNode���飬����indexOfCharArr��ʾÿ��Ҫ����datas�б� 
void convertCharArrToNodeArr(char **datas, tNode *father, int indexOfCharArr){
	//������datasĳһ��Ϊ��ʱ�ʹ���������Ҷ��� 
	if(datas[indexOfCharArr] == NULL) return;
	//�Ը��������ݸ�ֵ 
	if(indexOfCharArr == indexOfRoot) father->data = datas[indexOfCharArr][0];
	
	//���ñ���i���ڼ�¼��ǰdatas���еĸ�����ӽ�㼯���� 
	int i = 1; 
	//�������ñ���pre��Ϊ�˼�¼��ǰ����ǰһ���ֵܽ�㲢Ϊ�����ֵܽ�㸳ֵ 
	tNode *pre = NULL; 
	//���ڸ�����Ѿ���������ռ䣬�Ӷ�����Ҫ�ٷ���
	//����Ϊ��ǰ�ӽ�㼯�е������ӽ�����ռ䣬���ݹ�Ϊÿ�������ͬ���Ĳ��� 
	for(char c = datas[indexOfCharArr][i]; c != '\0'; c = datas[indexOfCharArr][++i]){
		//����ÿ���ӽ�㣬Ϊ�����ռ䣬����data��ֵ 
		tNode *child = (tNode *)malloc(sizeof(tNode));
		child->data = c;

		//���ӡ����ֵ�ָ����ʱ�ÿ� 
		child->lchild = child->rBrother = NULL;
		
		//��father������ָ�븳ֵ����ʱfather����ڲ����ݸ�ֵ��� 
		if(i == 1) father->lchild = child;
		
		//Ϊ��ǰ�ӽ���ǰһ���ֵܽ������ֵ�ָ�븳ֵ 
		if(pre) pre->rBrother = child;
		
		//��¼��ǰ�ӽ���ǰһ���ֵܽ�㣬�Ա�Ϊ��ǰһ���ֵܽ������ֵܽ�㸳ֵ 
		pre = child;
		
		//�Ե�ǰ�ӽ�����ͬ���Ĳ��� 
		convertCharArrToNodeArr(datas, child, c - 'A');
	}
} 

//�ú�����console��ȡ�û�����ĵ����������ݣ����洢����άchar�����з��� 
char **getInputDatas(){
	printf("���������ĸ����ֵ��ֵֻ����ASCII�ַ���ֻ����26����д��ĸ��\n");
	char c;
	scanf("%c", &c);
	indexOfRoot = c - 'A';
	
	printf("\n\n����A-B-C-D-E����ʽ�������������A������㣬BCDE����ø��ڵ��������������ĺ��ӽڵ㣺\n");
	printf("������������'#'�����س�\n");
	
	//�����ά���飬����ֻ��26�У���ΪҪ��Ľ�����ݱ����Ǵ�д��ĸ
	char **datas = (char **)malloc(sizeof(char *) * 26);
	//��datas�����ʼ�� 
	for(int i = 0; i < 26; i++)  datas[i] = NULL;
	
	//����temp���������ݴ���������� 
	char temp[20];
	while(1) {
		scanf("%s", temp);
		if(temp[0] == '#') break;
		
		//���㵱ǰ������ӽ�㼯���ڶ�άchar����������λ�� 
		int index = temp[0] - 'A';
		if(datas[index] != NULL){
			printf("����������ø��ڵ㼰�������ӽڵ㣬���������룡\n");
			continue; 
		}
		
		//��������������lengthOfAll��ʾ������ַ����ܳ��ȣ�lengthOfNodes��ʾ�ַ����еĽ����Ŀ 
		//ͳ�Ƶ�ǰ������ַ������� 
		int lengthOfAll = 0, lengthOfNodes = 0;
		while(temp[lengthOfAll] != '\n'){
			if(temp[lengthOfAll] != '-') lengthOfNodes++;	
			lengthOfAll++; 
		} 
		
		//����ǰ��õ��Ľ����Ŀ��Ϊ��Ӧ���ڵ������з���ռ䣬��������Ľ�㸳ֵ����Ӧλ�� 
		datas[index] = (char *)malloc(sizeof(char) * lengthOfNodes);
		for(int i = 0, j = 0; i < lengthOfAll; i++){
			if(temp[i] == '-') continue;
			datas[index][j++] = temp[i];
		}
	}
	
	return datas;
}
