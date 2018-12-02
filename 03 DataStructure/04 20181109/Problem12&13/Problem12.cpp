#include "definitions.h"

//����ñ�������ͳ�������ɭ�ֵĽ����� 
int numOfNodes = 0;

tNode *getLinkedNode(){
	//���ȴ�console��ȡ�û�����Ĵ������ĺ����ʾ����ɭ�����ݣ���������ʽ�洢 
	varDegreeNode *head = getDatasFromInput();
	
	//�ٴν���������ת��Ϊ˳��洢�ṹ 
	degreeNode **datas = convertLinkedListToArr(head);
	
	//��󽫴������ĺ�������ʾ����ɭ��ת��Ϊ��̬�������ֱ�ʾ����ɭ�� 
	return convertDegreeNodeToLinkedNode(datas);
}

//�ú�������console����õ���άɭ������ת��Ϊ��̬�������ֱ�ʾ����ɭ�������ĸ����ָ����ɵ�һά���� 
tNode *convertDegreeNodeToLinkedNode(degreeNode **datas){
	//����tNodeջ�������ݴ��Ѿ�����ռ䵫��û�н�������������ϵ�Ľ�� 
	tNode **stack = (tNode **)malloc(sizeof(tNode *) * numOfNodes);
	int top = -1;
	for(int i = 0; i < numOfNodes; i++){
		//Ϊ��ǰ�������������ֱ�ʾ�����Ŀռ� 
		tNode *temp = (tNode *)malloc(sizeof(tNode));
		temp->data = datas[i]->data;
		temp->lchild = temp->rBrother = NULL;
		
		//�����ǰ�����Ҷ�ڵ㣬��ô��ǰ���Ӧ����ջ
		if(datas[i]->degree == 0){
			++top;
			stack[top] = temp;
			continue; 
		}
		
		//���¶Զ�����Ϊ0�Ľ����д��� 
		if(datas[i]->degree == 1){ 
			//����Ϊ1�Ľ�㣬ֱ�ӵ���ջ���Ľ�㣬����������������Ϊ1�������� 
			temp->lchild = stack[top];
			top--;
		}else{
			//��������2�ķ�Ҷ��㽨�������ṹ�������������ĸ����ѹ��ջ�� 
			int j = top;
			//����preָ�����ڸ�ÿ���ӽ������ֵ�ָ�븳ֵ 
			tNode *pre = stack[top];
			top--;
			//����pָ������ÿ�����Ĳ���
			tNode *p;
			//���ڳ�ʼtop��������top���ֵ��degree��ͬʱ������ǰ���������ӽ�㶼�Ѳ������� 
			while(j - top != datas[i]->degree){
				//��ջ���ó���㸳ֵ��p����ʱpre��p�����ֵܣ�Ӧ����p�����ֵ�ָ�븳ֵΪpre 
				p = stack[top];
				top--;
				p->rBrother = pre;
				pre = p; 
			}
			//������preָ��ľ������ӣ�Ӧ���ѵ�ǰ���temp����ָ��ָ��pre 
			temp->lchild = p;
		}
	
		//�Ǹ����Ӧ��ѹ��ջ�� 
		++top;
		stack[top] = temp;
	}
	
	//��ѭ��������ջ��ʣ��Ľ������������ĸ���㣬���ǽ������ӵ�һ�𣬱�ʾ����ɭ��
	tNode *tempRoot;
	for(int i = 0; i < top; i++){
		//��Ȼǰһ��������i���������ֵܽ���Ǻ�һ���� 
		stack[i]->rBrother = stack[i + 1];
	}
	
	//ջ�׵Ľ�����ɭ�ֵĸ���Ҳ����ɭ���е�һ�����ĸ���� 
	return stack[0];
}



/* ���������봦���2�����������㷨��Ҫ���� */

//�ú�����console��ȡ������Դ������ĺ�������ʾ����ʾ��ɭ�����ݣ��������ά������ 
degreeNode **convertLinkedListToArr(varDegreeNode *head){
	//���û�������㣬���ؿ� 
	if(numOfNodes == 0)  return NULL;
	
	//����degreeNodeһά����ռ� 
	degreeNode **datas = (degreeNode **)malloc(sizeof(degreeNode *) * numOfNodes);
	
	//��ʼ��degreeNodeһά�����ÿ�������и�ֵ 
	varDegreeNode *p = head->next, *temp;
	//degreeNodeһά�����±� 
	int i = 0;
	while(p){
		//Ϊÿ����㸳ֵ 
		datas[i] = (degreeNode *)malloc(sizeof(degreeNode));
		datas[i]->data = p->data;
		datas[i]->degree = p->degree;
		
		//����ʹ�ù���varDegreeNode���Ӧ���ͷŵ� 
		temp = p;
		p = p->next;
		free(temp);
		
		i++;
	}
	
	return datas; 
}

//�ú�����console��ȡ������Դ������ĺ�������ʾ����ʾ��ɭ�����ݣ������������ʽ�洢 
varDegreeNode *getDatasFromInput(){
	//����ͷ��� 
	varDegreeNode *head = (varDegreeNode *)malloc(sizeof(varDegreeNode));
	head->next = NULL;
	
	printf("���ԡ����ֵ ����������ʽ����ɭ�����ݣ������������롰# -1���Ա�ʾ������ϣ�\n");
	varDegreeNode *p = head;
	while(1){
		char data;
		int degree;
		scanf("%c %d", &data, &degree);
		if(data == '#') break;
		
		//Ϊ��㸳ֵ 
		varDegreeNode *temp = (varDegreeNode *)malloc(sizeof(varDegreeNode));
		temp->data = data;
		temp->degree = degree;
		temp->next = NULL;
		
		//��pָ����һ����������ֵ 
		p->next = temp;
		p = p->next;
		
		//��¼�����Ŀ 
		numOfNodes++;
		
		//ȥ���������Ļس���
		removeEnterSymbol();
	}
	
	return head;
} 
