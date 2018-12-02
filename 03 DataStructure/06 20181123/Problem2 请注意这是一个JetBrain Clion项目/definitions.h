//
// Created by Administrator on 2018-11-29.
//

#ifndef PROBLEM_2_DEFINITIONS_H
#define PROBLEM_2_DEFINITIONS_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <stack>
using namespace std;
/*
 * sorting的函数定义
 */
//该函数将栈中的整数排序后返回
stack<int> sorting(stack<int> origin);


/*
 * fileInputUtil的函数定义
 */
//该函数从txt文件中读取未排序的数据，并以整型一维数组返回
stack<int> getDataFromFile(string path);

#endif //PROBLEM_2_DEFINITIONS_H
