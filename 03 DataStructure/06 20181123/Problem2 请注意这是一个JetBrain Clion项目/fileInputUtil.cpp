#include "definitions.h"

stack<int> getDataFromFile(string path){
    printf("��ע������Դtxt�ļ���·��������Ĭ��·����\nC:\\Users\\Administrator\\Desktop\\data.txt\n");
    stack<int> result;
    //ѡ��Դ�ļ�
    if(path.empty()) {
        printf("����main.cpp�ж���·����");
        return result;
    }

    FILE *dataFile = fopen(path.data(), "r");
    if(dataFile == nullptr){
        printf("·��%sû������Դ�ļ���", path.data());
        return result;
    }

    int temp;
    while(fscanf(dataFile,"%d", &temp) != EOF){
        result.push(temp);
    }

    return result;
}
