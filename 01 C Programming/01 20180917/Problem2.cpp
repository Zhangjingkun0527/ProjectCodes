#include "Headers.h"

void proc(char *str){
	//����start������¼Сд��ĸ������������ȷ��Ŀ�������д�д��ĸ��ʼλ�� 
	int start = 0, count = 0;
	char s = '.';
	//ͳ��str��Сд��ĸ�ĸ����������С,����ӡԭ�����Ա�۲���֤ 
	printf("The origin array: \n");
	for(int i = 0; s != '\0';i++){
		s = str[i];
		if(s != '\0'){
			printf("%c ", s);	
		}
		
		if(s < 123 && s > 96){
			start++;
		}
		count++;
	}
	//����Ŀ�����鲢�����ڴ� 
	char *result = (char *)malloc(sizeof(char) * count);
	//char����ʵ�ʳ���Ϊ���������ַ���\0���� ���ȣ�����Ӧ����1 
	count--;
	//����begin���������ڶ�λСд��ĸ��Ŀ��λ�� 
	int begin = 0;
	//��Ŀ��������и�ֵ���㣬Сд��ĸ��ǰ����д��ĸ�ں� 
	for(int i = 0; i < count; i++){
		if(str[i] < 123 && str[i] > 96){
			result[begin++] = str[i];
		}else{
			result[start++] = str[i];
		}
	}
	//��strָ��result���Խ�����д�ӡ�Ա�۲���֤ 
	str = result;
	printf("\n\nThe result: \n");
	for(int i = 0;i < count; i++){
		printf("%c ", str[i]);
	}
}
