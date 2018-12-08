#include "definitions.h"
//归并排序中的归并函数
void optimized_merge_function(int *origin, int left, int right, int middle);
//归并函数用到的暂存数组，只初始化一次
static auto temp_array = static_cast<int *>(malloc(sizeof(int) * (int)COUNT_OF_RANDOM_NUMBERS));

void general_merge_sort(int *origin, int left, int right){
    if(left < right){
        auto middle = (left + right) / 2;
        general_merge_sort(origin, left, middle);
        general_merge_sort(origin, middle + 1, right);
        optimized_merge_function(origin, left, right, middle);
    }
}

void optimized_merge_sort(int *origin, int left, int right, int threshold){
    if(right - left + 1 > threshold){
        auto middle = (left + right) / 2;
        optimized_merge_sort(origin, left, middle, threshold);
        optimized_merge_sort(origin, middle + 1, right, threshold);
        optimized_merge_function(origin, left, right, middle);
    }else insert_sort(origin, left, right);
}

void optimized_merge_function(int *origin, int left, int right, int middle){
    auto i = left;
    for(; i <= middle; ++i){
        temp_array[i] = origin[i];
    }

    auto j = right;
    for(; j > middle; --j){
        temp_array[j] = origin[middle + 1 + right - j];
    }

    //合并子数组
    i = left;
    j = right;
    auto k = left;
    while(i <= j){
        if(temp_array[i] <= temp_array[j]){
            origin[k] = temp_array[i];
            ++i;
        }else{
            origin[k] = temp_array[j];
            --j;
        }
        ++k;
    }
}