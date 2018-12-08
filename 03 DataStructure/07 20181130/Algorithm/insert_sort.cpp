#include "definitions.h"

void insert_sort(int *origin, int begin, int end){
    if(end < begin || origin == nullptr) return;

    for (auto i = begin; i <= end; ++i){
        for(auto j = i; j > begin; --j){
            //如果某位数大于它前面那个，就不用交换了，因为他前面的序列本身就是从小到大有序的
            //他前面的就是这个有序列最大的值，如果大就不用考虑交换
            if(origin[j] > origin[j - 1]) break;
            swap(origin[j], origin[j - 1]);
        }
    }
}