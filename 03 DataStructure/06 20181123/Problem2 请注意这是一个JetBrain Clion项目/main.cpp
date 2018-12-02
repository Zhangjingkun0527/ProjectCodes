#include "definitions.h"

int main() {

    //请在这里更改数据文件路径
    string path = "C:\\Users\\Administrator\\Desktop\\data.txt";
    auto originData = getDataFromFile(path);
    auto sortingResult = sorting(originData);
    //打印排序后的结果
    printf("排序后的结果是：\n");
    while(!sortingResult.empty()){
        printf("%d ", sortingResult.top());
        sortingResult.pop();
    }

    printf("\n\n");
    system("pause");
    return 0;
}