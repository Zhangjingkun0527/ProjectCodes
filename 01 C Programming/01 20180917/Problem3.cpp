#include "Headers.h"

void findSymmetryChars(char *str){
	//定义length统计str总长度，定义startLength定义开始起始长度 
	int length = 0;
	char s = str[0];
	for(int i = 0; s != '\0';s = str[i++]){
		length++;
	}
	length--;

	
	int path[i] = {0};
	
	//设定外层循环，遍历从0~length-2位置每个字符，判断它们是否会出现对称 
	for(int i = 0; i < length - 2; i++){
		//设定内层循环，判断 
		for(int j = i; j < length; j++) {
			
		}
	}
	
	for(int k = i; k < i * 2 + j; k++){
		printf("%c ", str[k]);
	}
}                                               
