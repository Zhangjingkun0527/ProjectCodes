#include "definitions.h"

void insert_sort(int *origin, int begin, int end){
    if(end < begin || origin == nullptr) return;

    for (auto i = begin; i <= end; ++i){
        for(auto j = i; j > begin; --j){
            //���ĳλ��������ǰ���Ǹ����Ͳ��ý����ˣ���Ϊ��ǰ������б�����Ǵ�С���������
            //��ǰ��ľ����������������ֵ�������Ͳ��ÿ��ǽ���
            if(origin[j] > origin[j - 1]) break;
            swap(origin[j], origin[j - 1]);
        }
    }
}