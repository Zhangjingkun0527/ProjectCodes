//
// Created by Administrator on 2018-11-29.
//

#ifndef PROBLEM7_DEFINITIONS_H
#define PROBLEM7_DEFINITIONS_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

/*
 * sortingUsingTernaryTree的函数定义
 */
//使用三叉树并以大顶堆形式进行排序
void sorting(vector<int> &origin);

/*
 * fileInputUtil的函数定义
 */
//该函数从txt文件中读取未排序的数据，并以vector返回
vector<int> getDataFromFile(string path);

#endif //PROBLEM7_DEFINITIONS_H
