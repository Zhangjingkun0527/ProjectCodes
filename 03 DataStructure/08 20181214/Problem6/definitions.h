#ifndef ALGORITHM_DEFINITIONS_H
#define ALGORITHM_DEFINITIONS_H

#include <cstdio>
#include <cstdlib>

#define NOT_FOUND -1

/**
 * 第6题问题1，m = 2时写出一个n²算法，找到是否存在和等于给定值K
 *
 * @param arr 目标数组
 * @param count 数组长度
 * @param K 给定值K
 * @return 是否存在这样2个数在目标数组中和等于K
 */
bool question_1(int *arr, int count, int K);

/**
 * 第6题问题2，m = 2时写出一个n log n算法，找到是否存在和等于给定值K
 *
 * @param arr 目标数组
 * @param count 数组长度
 * @param K 给定值K
 * @return 是否存在这样2个数在目标数组中和等于K
 */
bool question_2(int *arr, int count, int K);

/**
 * 第6题问题3，m = 3时写出一个n²算法，找到是否存在和等于给定值K
 *
 * @param arr 目标数组
 * @param count 数组长度
 * @param K 给定值K
 * @return 是否存在这样3个数在目标数组中和等于K
 */
bool question_3(int *arr, int count, int K);

/**
 * 第6题问题4，m = 4时写出一个n² log n算法，找到是否存在和等于给定值K
 *
 * @param arr 目标数组
 * @param count 数组长度
 * @param K 给定值K
 * @return 是否存在这样4个数在目标数组中和等于K
 */
bool question_4(int *arr, int count, int K);



/**
 * 随机生成值域在[lower_bound, upper_bound]之间的数
 *
 * @param count 数组元素数量
 * @param lower_bound 值域下界
 * @param upper_bound 值域上界
 * @return 数组首地址
 */
int *generator_random_numbers(int count, int lower_bound, int upper_bound);

/**
 * 二分检索法，然后返回所在下标，如果没找到则返回false。
 * 二分检索法要求数组正序排列
 *
 * @param arr 查找数组
 * @param key 查找关键之
 * @param count 数组长度
 * @param begin 查找起始下标
 * @param end 查找终点下标
 * @return 返回匹配值所在下标
 */
int binary_search(int *arr, int key, int count, int begin, int end);

/**
 * 二维数组的二分检索(按照某一列查找)，返回二维数组行下标
 *
 * @param arr 二维数组
 * @param key 查找关键之
 * @param count 数组长度
 * @param begin 查找起始下标
 * @param end 查找终点下标
 * @param index 查找列的下标
 * @return 返回匹配值所在下标
 */
int binary_search_for_two_dimension_array(int **arr, int key, int begin, int end, int index);

/**
 * 用于快排的比较函数
 *
 * @param a 关键值a
 * @param b 关键值b
 * @return 大小
 */
int cmp_for_one_dimension_array(const void *a, const void *b);

/**
 * 找到数组中的最大值，要求数组全部都是正整数
 *
 * @param arr 目标数组
 * @param begin 起始下标
 * @param end 终点下标
 * @return 最大值
 */
int find_max_in_array(const int *arr, int begin, int end);

/**
 * 该比较函数用于二维数组排序
 *
 * @param a 二维数组
 * @param b 二维数组
 * @param index 用于排序的基准列
 * @return 大小
 */
int cmp_for_two_dimension_array(const void *a, const void *b);

/**
 * 交换函数
 * @tparam T
 * @param a
 * @param b
 */
template <typename T>
void swap(const T &a, const T &b);

/**
 * 为二维数组排序定制的快速排序，
 * @param origin 二维数组
 * @param left 区间起始下标
 * @param right 区间终端下标
 * @param index 排序所根据的二维数组列
 * @param row_length 二维数组每行的长度
 */
void general_quick_sort_for_two_dimension_array(int **origin, int left, int right, int index, int row_length);
#endif //ALGORITHM_DEFINITIONS_H
