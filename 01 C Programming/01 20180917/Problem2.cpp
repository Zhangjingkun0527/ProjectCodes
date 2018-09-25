#include "Headers.h"

void proc(char *str){
	//定义start变量记录小写字母个数，并用于确定目标数组中大写字母开始位置 
	int start = 0, count = 0;
	char s = '.';
	//统计str中小写字母的个数和数组大小,并打印原数组以便观察验证 
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
	//定义目标数组并分配内存 
	char *result = (char *)malloc(sizeof(char) * count);
	//char数组实际长度为包含结束字符‘\0’的 长度，这里应当减1 
	count--;
	//定义begin变量，用于定位小写字母的目标位置 
	int begin = 0;
	//对目标数组进行赋值运算，小写字母在前，大写字母在后 
	for(int i = 0; i < count; i++){
		if(str[i] < 123 && str[i] > 96){
			result[begin++] = str[i];
		}else{
			result[start++] = str[i];
		}
	}
	//将str指向result，对结果进行打印以便观察验证 
	str = result;
	printf("\n\nThe result: \n");
	for(int i = 0;i < count; i++){
		printf("%c ", str[i]);
	}
}
