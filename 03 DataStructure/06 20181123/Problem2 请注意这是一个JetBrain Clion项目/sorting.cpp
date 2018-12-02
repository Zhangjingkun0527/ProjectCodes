#include "definitions.h"

stack<int> sorting(stack<int> origin){
    //结果栈
    stack<int> sortingResult;
    //如果原始数据为空，返回空栈
    if(origin.empty()) return sortingResult;

    sortingResult.push(origin.top());
    origin.pop();
    stack<int> temp;
    //如果原数据栈不空，代表还没结束
    while(!origin.empty()){
        //如果结果栈顶部元素大于原数据栈，那么直接压入即可
        if(sortingResult.top() >= origin.top()){
            sortingResult.push(origin.top());
            origin.pop();
        }else{
            //如果结果栈顶元素并非大于原数据栈，那么我们需要找到插入位置，而此时不符合条件的数据
            //应当存储在temp中
            while(!sortingResult.empty() && sortingResult.top() < origin.top()){
                temp.push(sortingResult.top());
                sortingResult.pop();
            }

            //将原数据栈的栈顶输入插入到合适位置
            sortingResult.push(origin.top());
            origin.pop();

            //将被存在temp中的数据放回结果栈
            while(!temp.empty()){
                sortingResult.push(temp.top());
                temp.pop();
            }
        }
    }

    return sortingResult;
}