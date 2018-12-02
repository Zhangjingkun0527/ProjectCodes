#include "definitions.h"

int main() {

    string path = "C:\\Users\\Administrator\\Desktop\\data.txt";
    auto originData = getDataFromFile(path);
    sorting(originData);
    printf("排序后的结果如下所示：\n");
    for(int i : originData){
        printf("%d ", i);
    }

    printf("\n\n");
    return 0;
}