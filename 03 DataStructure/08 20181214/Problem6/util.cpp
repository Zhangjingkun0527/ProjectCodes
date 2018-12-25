#include "definitions.h"

int cmp_for_one_dimension_array(const void *a, const void *b){
    //这是从小到大排序，若是从大到小改成： return *(int *)b-*(int *)a;
    return *(int *)a - *(int *)b;
}

int cmp_for_two_dimension_array(const void *a, const void *b){
    int *ap = *(int **)a;
    int *bp = *(int **)b;

    return ap[0] - bp[0];
}

int find_max_in_array(const int *arr, int begin, int end) {
    auto max = 0;
    for(int i = begin; i <= end; ++i) {
        if(arr[i] > max) max = arr[i];
    }

    return max;
}