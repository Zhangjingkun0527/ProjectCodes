#include "definitions.h"

stack<int> getDataFromFile(string path){
    printf("请注意数据源txt文件的路径，程序默认路径是\nC:\\Users\\Administrator\\Desktop\\data.txt\n");
    stack<int> result;
    //选择源文件
    if(path.empty()) {
        printf("请在main.cpp中定义路径！");
        return result;
    }

    FILE *dataFile = fopen(path.data(), "r");
    if(dataFile == nullptr){
        printf("路径%s没有数据源文件！", path.data());
        return result;
    }

    int temp;
    while(fscanf(dataFile,"%d", &temp) != EOF){
        result.push(temp);
    }

    return result;
}
