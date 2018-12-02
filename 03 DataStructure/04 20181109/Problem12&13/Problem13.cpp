#include "definitions.h"

//����ñ�������ͳ�������ɭ�ֵĽ����� 
int countOfNodes = 0;
//����ñ�����������������nodeArr��ǰ����±��ָ�룬���ڸ��ߵ�ǰ��ӵ��ĸ�λ���� 
int indexOfNodeArr = 0;
//�����һά���飬��Ϊ�˼�¼ÿ�������preNode�е�λ�� 
int *indexOfRlink;

//�ú������õ��Ĵ������ĺ������д�ӡ����
void printDegreeNodes(){
	//�ȴ�console��ȡ���� 
	varPreNode *head = getDatasFromConsole();
	
	//����ȡ��������ת��ΪpreNode���� 
	preNode **preNodeArr = convertCharArrToPreNodeArr(head);
	
	//��ȡÿ�����Ķ��� 
	int *degrees =  getDegreeFromPreNodeArr(preNodeArr);
	//���ݽ��������������ĺ������б�ʾ��������ռ� 
	degreeNode **nodeArr = (degreeNode **)malloc(sizeof(degreeNode *) * countOfNodes);
	//�õ��������� 
	getDegreeNodesFromPreNodeArr(preNodeArr, 0, degrees, nodeArr);
	
	//��ӡ��� 
	printf("ת���õ��ĺ������м�����Ϊ��\n");
	for(int i = 0; i < countOfNodes; i++){
		printf("%c %d\n",nodeArr[i]->data, nodeArr[i]->degree);
	}
} 

/*
	���������ݹ��ȡ�������д����nodeArr�� 
	����˵����
		1��arr�Ǵ��������������б�ʾ���Ľ������
		2��index��arr��ָ�룬ָʾÿ�εݹ�ʱ���������ĸ�arr�Ľ��
		3��degreeArr�Ǽ���õ���ÿ�����Ķ���
		4��nodeArr��Ԥ�ȷ���õĴ������ĺ������б�ʾ�������飬�ڸú����еõ����ģ����ս��Ҳ�Ǵ���������
		
	����˼�룺
		������������������оͱ�ʾɭ�֣�ͨ������ltag��ֱ��֪��ÿ���������ӣ�rlink��֪�����ֵܣ���˿����������ֱ�ӽ���
		����������ɵõ��������� 
*/
void getDegreeNodesFromPreNodeArr(preNode **arr, int index, int *degreeArr, degreeNode **nodeArr){
	//���ڴ���indexOfArr��preNode��㣬Ӧ���ȿ������Ƿ������ӣ����û����ֱ����ӽ���nodeArr
	//��������ӣ�Ӧ�����������ӽ���ͬ������ 
	if(!arr[index]->ltag){
	 	//��������ʱ�������ӽ���ͬ���������ڵ�ǰ�������Ӿ��ǽ����ŵ�ǰ��㣬���index+1
		//���ﲻ�ÿ������һ����㣬��Ϊ�������е����һ�����һ����Ҷ��㡣 
		getDegreeNodesFromPreNodeArr(arr, index + 1, degreeArr, nodeArr);
	}
	
	//����������nodeArr[index]�������ʱ��������Ӧ���������������У����������ڶ���������������
	visit(arr, index, degreeArr, nodeArr);
	
	//�������굱ǰ�������������������Ӧ�������������ֵ� 
	if(arr[index]->rlink != NULL){
		//��ǰ������������ʱ��Ӧ��������ͬ�Ĵ���
		//���ڱ������Ǹ���preNode��index����ÿ����������Ծ�����������index��ô���޷�����ÿ����������
		//�����뺯�����֣�indexOfRlink����ÿ������dataֵΪ������¼��������preNode�е��±� 
		getDegreeNodesFromPreNodeArr(arr, indexOfRlink[arr[index]->rlink->data - '#'], degreeArr, nodeArr);
	}    
	
}

//��ֵ��������indexλ�õ�preNode��degreeArrֵ�����������ĺ������б�ʾ������nodeArr
void visit(preNode **arr, int index, int *degreeArr, degreeNode **nodeArr) {
	//���û�����ӣ�����ΪnodeArr[indexOfNodeArr]����ռ� 
	nodeArr[indexOfNodeArr] = (degreeNode *) malloc(sizeof(degreeNode));
	//��data��ֵ 
	nodeArr[indexOfNodeArr]->data = arr[index]->data;
	//��������ֵ 
	nodeArr[indexOfNodeArr]->degree = degreeArr[arr[index]->data - '#'];
	//nodeArrָ�� ����1 
	indexOfNodeArr++;
}


//�ú�������ͳ�ƴ��������ȸ������ʾ����ɭ����ÿ�����Ķ�����������ASCIIֵ��Ϊchar�����±귵�� 
int *getDegreeFromPreNodeArr(preNode **arr){
	//������䳤��Ϊ92���������ڷ���ʹ�ù�ϣ����rlink��ֵ����Ϊ����ʱҪ��������ַ�ֻ������35~126��ASCII�ַ� 
	int *degreeArr = (int *)malloc(sizeof(int) * 92);
	
	//����forѭ��ͳ��ÿ�����Ķ��� 
	preNode *p;
	int index = 0;
	int degree = 0;
	for(int i = 0; i < countOfNodes; i++){
		//ÿ��ͳ�ƣ���index��degree��0 
		index = 0;
		degree = 0;
		
		//index���Ե�ǰ���arr[i]��ֵȷ���Ĺ�ϣ�±� 
		index = arr[i]->data - '#';
		
		//������arr[i]�����ӣ���ô���������ӵ��������ͳ�ƶ��� 
		//����Ҫ���ǵ�ǰ����ǲ������һ����㣬���һ�����һ����Ҷ��㣬ֱ������Ϊ0���� 
		if(!arr[i]->ltag && i != countOfNodes + 1){
			//���arr[i]�����ӣ���ôarr[i+1]һ������������ 
			p = arr[i + 1];
			//�������ӵ��������ͳ�ƶ��� 
			while(p) {
				degree++;
				p = p->rlink;
			}
		}
		degreeArr[index] = degree;
	}
	
	return degreeArr;
}


/* ���������봦���3�����������㷨��Ҫ���� */

//�ú�����convertVarPreNodesToCharArr()��ȡ���Ķ�άchar����ת��ΪpreNode����
preNode **convertCharArrToPreNodeArr(varPreNode *head){
	//����pָ�������ͷ����һ����㣬����ѭ����ֵ 
	varPreNode *p = head->next;
	
	//����preNode��ָ������ 
	preNode **nodeArr = (preNode **)malloc(sizeof(preNode *) * countOfNodes);
	
	//������䳤��Ϊ92���������ڷ���ʹ�ù�ϣ����rlink��ֵ����Ϊ����ʱҪ��������ַ�ֻ������35~126��ASCII�ַ�
	//���ڶ�ÿ����㸳ֵʱ��ʵ����ֻ��֪��������Ӧ����dataֵ����������ĵ�ַ�����ｫ���ǰ��������Լ���data��Ӧ���±����
	//tempArr��������rlink��ֵʱ������ÿ������õ�rlinkֵ�Ϳ��Դ�tempArr�л�ȡ����ַ 
	preNode **tempArr = (preNode **)malloc(sizeof(preNode *) * 92);
	
	//����Ϊ�ļ�ͷ�����indexOfRlink����ռ䣬������Ҫ�������������еݹ��ȡ��������ʱ��ÿ������rlink����ʱ������rlink
	//��preNode�����У���ΪpreNode�����rlink��ָ�룬ָ�����ֵܽ�㣬���ǲ���֪�����ֵܽ����preNode�е�λ�ã�������ﲻ��¼
	//��ôÿ�ζ�Ҫ����preNode��ȡrlink����preNode�����е��±꣬������ݹ麯���Ľ����� 
	//��������������ǿ���ͨ��preNode��dataֵ�Ӹ��������õ�����preNode�е��±�λ�ã�����ÿ������rlink����
	//preNode�е��±�Ҳ���ܹ��õ��ˣ����ǻ���ÿ������ֵ�����ظ��ļ���ǰ�� 
	indexOfRlink = (int *)malloc(sizeof(int) * 92);
	
	//��һ��ѭ����Ϊÿ����㴴�����ռ䣬������ltag��dataֵ
	int i = 0;
	
	while(p) {
		nodeArr[i]  = (preNode *)malloc(sizeof(preNode));
		//datas�е�3λ�ַ��ֱ��ʾltag data rlinkֵ 
		nodeArr[i]->ltag = p->ltag; 
		nodeArr[i]->data = p->data;
		nodeArr[i]->rlink = NULL;
		
		//���ݽ���ֵ��Ӧ�Ĺ�ϣ�±꣬����tempArr�� 
		int index = p->data - '#';
		tempArr[index] = nodeArr[i];
		
		//��¼ÿ�������preNode�е��±�λ�� 
		indexOfRlink[index] = i;
		
		i++;
		p = p->next; 
	}
	
	//�ڶ���ѭ��Ϊÿ������rlink��ֵ�����Ƚ�i��p��ʼ�� 
	i = 0; 
	p = head->next;
	while(p){
		//�����ǰ���û�����ֵܣ���rlink�ÿ� 
		if(p->rlink == '!'){
			nodeArr[i]->rlink = NULL;
		}else{
			int index = p->rlink - '#';
			nodeArr[i]->rlink = tempArr[index];
			//�������ÿ������¼�������ֵ��� 
			indexOfRlink[i] = index;	
		}
		
		i++;
		p = p->next;
	}
	
	free(tempArr);
	return nodeArr;
}


//��console��ȡ�û���������ݣ���ת��Ϊ�ɱ䳤������洢 
varPreNode *getDatasFromConsole(){
	//����ͷ��� 
	varPreNode *head = (varPreNode *)malloc(sizeof(varPreNode));
	head->next = NULL;
	
	printf("���ԡ����ֵ ltag ���ֵܽ��ֵ������ʽ����ɭ�����ݣ����硰1 A B���������ָ����ֵ��������Ӣ��̾��!��ʾ�ޣ����硰1 A !����\n");
	printf("�����������ֵֻ����ʮ����ֵλ��35~126��ASCIIֵ����33λ��Ӣ��̾��!����35λ��#����126λ��~��\n");
	printf("������������ ��! 0 !���Ա�ʾ������ϣ�����Ҫ��ÿ������ֵ�����ظ���\n");
	varPreNode *p = head;
	while(1){
		char data;
		int ltag;
		char rlink;
		
		scanf("%c %d %c", &data, &ltag, &rlink);
		if(data == '!') break;
		
		//Ϊ��㸳ֵ 
		varPreNode *temp = (varPreNode *)malloc(sizeof(varPreNode));
		temp->data = data;
		temp->ltag = ltag;
		temp->rlink = rlink;
		temp->next = NULL;
		
		//��pָ����һ����������ֵ 
		p->next = temp;
		p = p->next;
		
		//��¼�����Ŀ 
		countOfNodes++;
		
		//ȥ���س��� 
		removeEnterSymbol();
	}
	
	return head;
}
