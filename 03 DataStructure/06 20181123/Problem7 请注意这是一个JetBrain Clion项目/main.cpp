#include "definitions.h"

int main() {

    string path = "C:\\Users\\Administrator\\Desktop\\data.txt";
    auto originData = getDataFromFile(path);
    sorting(originData);
    printf("�����Ľ��������ʾ��\n");
    for(int i : originData){
        printf("%d ", i);
    }

    printf("\n\n");
    return 0;
}