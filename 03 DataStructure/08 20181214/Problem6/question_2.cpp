#include "definitions.h"

/**
 * 第6题问题2，m = 2时写出一个n log n算法，找到是否存在和等于给定值K
 *
 * @param arr 目标数组
 * @param count 数组长度
 * @param K 给定值K
 * @return 是否存在这样2个数在目标数组中和等于K
 */
bool question_2(int *arr, int count, int K) {
    //复制一份数组
    auto arr_copy = static_cast<int *>(malloc(sizeof(int) * count));
    for(auto i = 0; i < count ; ++i) {
        arr_copy[i] = arr[i];
    }
    //首先对数组排序，复杂度n log n
    qsort(arr_copy, static_cast<size_t >(count), sizeof(arr_copy[0]), cmp_for_one_dimension_array);

    //由于二分检索复杂度为log n，因此以下代码块复杂度为n log n
    for(int i = 0; i < count; ++i) {
        auto temp = K - arr_copy[i];
        auto result = binary_search(arr_copy, temp, count, i + 1, count - 1);
        //必须去除同一个数被用了两次的情况
        if(result == i) continue;
        if(result == NOT_FOUND) continue;
        return true;
    }
    return false;
}