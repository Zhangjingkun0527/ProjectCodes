#include "definitions.h"

/**
 * 第6题问题1，m = 2时写出一个n²算法，找到是否存在和等于给定值K
 *
 * @param arr 目标数组
 * @param count 数组长度
 * @param K 给定值K
 * @return 是否存在这样2个数在目标数组中和等于K
 */
bool question_1(int *arr, int count, int K) {
    for(int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if(arr[i] + arr[j] == K) return true;
        }
    }

    return false;
}
