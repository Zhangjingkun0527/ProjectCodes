#include "Headers.h"

void findSymmetryChars(char *str){
	//����lengthͳ��str�ܳ��ȣ�����startLength���忪ʼ��ʼ���� 
	int length = 0;
	char s = str[0];
	for(int i = 0; s != '\0';s = str[i++]){
		length++;
	}
	length--;

	
	int path[i] = {0};
	
	//�趨���ѭ����������0~length-2λ��ÿ���ַ����ж������Ƿ����ֶԳ� 
	for(int i = 0; i < length - 2; i++){
		//�趨�ڲ�ѭ�����ж� 
		for(int j = i; j < length; j++) {
			
		}
	}
	
	for(int k = i; k < i * 2 + j; k++){
		printf("%c ", str[k]);
	}
}                                               
