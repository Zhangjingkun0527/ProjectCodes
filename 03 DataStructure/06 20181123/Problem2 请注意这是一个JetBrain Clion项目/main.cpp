#include "definitions.h"

int main() {

    //����������������ļ�·��
    string path = "C:\\Users\\Administrator\\Desktop\\data.txt";
    auto originData = getDataFromFile(path);
    auto sortingResult = sorting(originData);
    //��ӡ�����Ľ��
    printf("�����Ľ���ǣ�\n");
    while(!sortingResult.empty()){
        printf("%d ", sortingResult.top());
        sortingResult.pop();
    }

    printf("\n\n");
    system("pause");
    return 0;
}