#include "definitions.h"

/**
 * 第6题问题3，m = 3时写出一个n²算法，找到是否存在和等于给定值K
 *
 * @param arr 目标数组
 * @param count 数组长度
 * @param K 给定值K
 * @return 是否存在这样3个数在目标数组中和等于K
 */
bool question_3(int *arr, int count, int K) {
    //找到数组中的最大值
    auto max = find_max_in_array(arr, 0, count - 1);
    //分配一个长度和最大值+1一样的数组，用来标记arr中元素的分布情况，用于判断
    auto existing_symbol = static_cast<int *>(malloc(sizeof(int) * (max + 1)));
    for(int i = 0; i < count; ++i) {
        existing_symbol[i]= 0;
    }

    for(int i = 0; i < count; ++i) {
        ++existing_symbol[arr[i]];
    }

    //设置i=0，从左开始遍历，首先用K减去arr[i]，现在要在剩下的数组中找到两个数看能不能等于K-arr[i]
    //内循环设置j=i+1对剩余数组遍历，再用K-arr[i]-arr[j]，判断它在existing_symbol中是否存在
    //如果存在就意味着原数组存在这样3个数使得它们的和等于K
    //这个算法复杂度是n²
    for(int i = 0; i < count; ++i) {
        auto temp_1 = K - arr[i];
        if(temp_1 < 0) continue;
        //对于原数组中每个值，使用后，在existing_symbol中的计数应当减1,防止重复使用
        --existing_symbol[arr[i]];
        for(int j = i + 1; j < count; ++j) {
            auto temp_2 = temp_1 - arr[j];
            //同上
            --existing_symbol[arr[j]];

            if(temp_2 >= 0 && existing_symbol[temp_2] > 0)
                return true;

            //对于内层循环，数使用后要加回来，因为它在外层循环会被用到
            ++existing_symbol[arr[j]];
        }
    }

    return false;
}