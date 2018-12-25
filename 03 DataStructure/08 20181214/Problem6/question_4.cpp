#include "definitions.h"

/**
 * 第6题问题4，m = 4时写出一个n² log n算法，找到是否存在和等于给定值K
 *
 * @param arr 目标数组
 * @param count 数组长度
 * @param K 给定值K
 * @return 是否存在这样4个数在目标数组中和等于K
 */
bool question_4(int *arr, int count, int K) {
    //创造一个n(n-1)/2的二维数组，第一列用于存储任意两个数相加的和，将其转换为问题1的解决
    //第二、三列存储两个数的下标，用于排出同一个数被重复使用
    auto length_of_two_sum_arr = (count - 1) * count / 2;
    auto two_sum_arr = static_cast<int **>(malloc(sizeof(int *) * length_of_two_sum_arr));
    //初始化
    for(auto i = 0; i < length_of_two_sum_arr; ++i) {
        two_sum_arr[i] = static_cast<int *>(malloc(sizeof(int) * 3));
        two_sum_arr[i][0] = two_sum_arr[i][1] = two_sum_arr[i][2] = -1;
    }
    auto k = 0;
    for(auto i = 0; i < count; ++i) {
        for(auto j = i + 1; j < count; ++j) {
            two_sum_arr[k][0] = arr[i] + arr[j];
            two_sum_arr[k][1] = i;
            two_sum_arr[k][2] = j;
            ++k;
        }
    }

    //对生成的任意两数和进行排序，复杂度为n² log n²=n² log n
    qsort(two_sum_arr, static_cast<size_t >(length_of_two_sum_arr), sizeof(two_sum_arr[0]), cmp_for_two_dimension_array);

    //使用问题2的n log n算法解决，其中n = n²，因此这个步骤的算法复杂度为n² log n²=n² log n
    //综上，本算法的复杂度为n² log n
    for(auto i = 0; i < length_of_two_sum_arr; ++i) {
        auto temp = K - two_sum_arr[i][0];
        auto result = binary_search_for_two_dimension_array(two_sum_arr, temp, i + 1, length_of_two_sum_arr - 1, 0);
        //必须去除同一个数被用了两次的情况
        if(result == i) continue;
        if(result == NOT_FOUND) continue;
        //必须判断四个数中是否有重复出现
        auto is_duplicated = (two_sum_arr[result][1] == two_sum_arr[i][1])
                || (two_sum_arr[result][1] == two_sum_arr[i][2])
                || (two_sum_arr[result][2] == two_sum_arr[i][1])
                || (two_sum_arr[result][2] == two_sum_arr[i][2]);
        if(is_duplicated) continue;
        return true;
    }

    return false;
}