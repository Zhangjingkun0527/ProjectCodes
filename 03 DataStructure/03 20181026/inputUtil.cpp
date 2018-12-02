#include "headers.h" 
//������ļ��ڵ�ȫ�ֱ��������ڼ�¼�������±� 
int indexOfRoot = -1;

//�ú������ظ������봴���Ķ����������ָ�� 
BiTreeNode *getRootOfBinaryTreeFromInput(){
	char **datas = getInputData();
	BiTreeNode *root;
	root = convertCharArrayIntoBiTreeNode(datas, NULL, indexOfRoot);
	return root;
}

//��������ݹ鴴�������� 
BiTreeNode *convertCharArrayIntoBiTreeNode(char **datas, BiTreeNode *root, int index){
	//���ݹ��ѯ����Ҷ�ڵ�ʱ���򷵻�NULL 
	if(datas[index][0] == '\n') return NULL;
	
	//��Ҷ�ڵ㣬���ȸ�root����ռ� 
	root = (BiTreeNode *)malloc(sizeof(BiTreeNode));

	//��Ҷ�ڵ��ֵΪdatas�����ж�Ӧ�±길���ֵ
	root->data = datas[index][0];
	root->lchild = NULL;
	root->rchild = NULL;
	
	//Ϊ���Ӹ�ֵ 
	BiTreeNode *templ = convertCharArrayIntoBiTreeNode(datas, root->lchild, datas[index][1]);
	//���templ��NULL����˵��������Ҷ�ӽ�㣬ֱ��Ϊ�丳ֵ 
	if(templ == NULL && datas[index][1] != '\n'){
		root->lchild = (BiTreeNode *)malloc(sizeof(BiTreeNode));
		root->lchild->data = datas[index][1];
		root->lchild->lchild = NULL;
		root->lchild->rchild = NULL;
	}else root->lchild = templ;
	
	//Ϊ�Һ��Ӹ�ֵ 
	BiTreeNode *tempr = convertCharArrayIntoBiTreeNode(datas, root->rchild, datas[index][2]);
	//���tempr��NULL����˵���Һ�����Ҷ�ӽ�㣬ֱ��Ϊ�丳ֵ 
	if(tempr == NULL && datas[index][2] != '\n'){
		root->rchild = (BiTreeNode *)malloc(sizeof(BiTreeNode));
		root->rchild->data = datas[index][2];
		root->rchild->lchild = NULL;
		root->rchild->rchild = NULL;
	}else root->rchild = tempr;
	
	return root;
} 

//�������뺯������console�˻�ȡ����Ķ��������ݣ���A-B-L��ʽ��ʾ���ڵ�-�ӽڵ�-���ӣ����ز�ֹ����BiTreeNode��ά����
//������ǰ�϶�����������е�dataֵֻ��ΪChar���Ӷ������ù�ϣ������ �����ȸ���256��ASCII�ַ� 
char **getInputData(){
	//�ö�ά����洢���е�ֵ 
	char **datas = (char **)malloc(sizeof(char *) * 256);
	for(int i = 0; i < 256; i++){
		//ÿ�д洢3��ֵ�������ֵ(0)�����ӽڵ�ֵ(1)���Һ��ӽ��ֵ(2)��ȫ����ʼ��Ϊ'\n' 
		datas[i]  = (char *)malloc(sizeof(char) * 4);
		datas[i][0] = datas[i][1] = datas[i][2] = '\n';
	}
	
	//�������ø��ڵ� 
	printf("�������������ֵ��ֵֻ����ACSII�ַ���\n");
	char root;
	scanf("%c", &root);
	indexOfRoot = root;
	
	printf("\n\n");
	printf("����������������н���ϵ����A-B-L��ʽ���룬����A��ʾ���ڵ�ֵ��B��ʾ���ӽ��ֵ��L��ʾ���Һ��ӽ��ı�ǡ�\n\n");
	printf("***�����ڵ��Ƕ���������㣬����A-B-L-t��A-B-L-T������ʶ�����յĽ�β�Ե�������'#'������***\n\n");

	
	//������ʱ���������ݴ����������
	char temp[8];
	int index = 0;
	while(1) {
		scanf("%s", temp);
		
		//������������'#'ʱ��ֹ���� 
		if(temp[0] == '#')  break;
		
		//�����ڵ��ֵ��Ϊ��ϣ�����±� 
		index = temp[0];
		
		//�жϵ�ǰ����Ƿ�Ϊ���ڵ㣬��������indexOfRoot��ֵ 
		if((temp[6] == 'T' || temp[6] == 't') && indexOfRoot != -1){
			indexOfRoot = index;
		}
		
		//����ñ�����Ϊ�˼򻯴��� 
		bool isLeftChild = temp[4] == 'L' || temp[4] == 'l';
		datas[index][0] = temp[0];
		if(temp[4] == 'L' && datas[index][1] == '\n'){
			datas[index][1] = temp[2];
			continue;
		}else if(temp[4] == 'L' && datas[index][1] != '\n'){
			//������Ľ����Ѿ�����ʱ���ж��Ƿ�Ҫ���� 
			printf("�����Ϊ%c�����ӽ���Ѿ����ڣ�ֵΪ%c���Ƿ񸲸ǣ�������1����֮����0��\n", temp[4], datas[index][1]);
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
			//������Ľ����Ѿ�����ʱ���ж��Ƿ�Ҫ���� 
			printf("�����Ϊ%c�����ӽ���Ѿ����ڣ�ֵΪ%c���Ƿ񸲸ǣ�������1����֮����0��\n", temp[4], datas[index][1]);
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
