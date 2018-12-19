#ifndef ALGORITHM_DEFINITIONS_H
#define ALGORITHM_DEFINITIONS_H

#include <cstdio>
#include <stdlib.h>

//随机数的数量，下界，上界，可以使用e表达式
#define COUNT_OF_RANDOM_NUMBERS 1e4
#define LOWER_BOUND 1
#define UPPER_BOUND 2e4

#define NOT_FOUND -1

/**
 * 随机数生成函数，只生成整型Int范围内的随机数
 * @param count 随机数的个数
 * @param lower_bound 随机数下界
 * @param upper_bound 随机数上界
 * @return 返回随机数数组的指针
 */
int *generator_random_numbers(int count, int lower_bound, int upper_bound);

/**
 * 顺序检索
 * @param arr 检索数组
 * @param key 被检索的值
 * @param count_of_search
 * @return 查找结果，如果没有找到则返回-1，如果找到则返回下标
 */
int sequential_search(int *arr, int key, int &count_of_search);

/**
 * 打印顺序检索查找总次数、查找成功次数、查找成功百分比等题目要求的数据
 */
void print_search_times_for_sequential_search();


/**
 * 二分检索
 * @param arr 检索数组
 * @param key 被检索的值
 * @param count_of_search
 * @return 查找结果，如果没有找到则返回-1，如果找到则返回下标
 */
int binary_search(int *arr, int key, int &count_of_search);

/**
 * 打印顺序检索查找总次数、查找成功次数、查找成功百分比等题目要求的数据
 */
void print_search_times_for_binary_search();

#endif //ALGORITHM_DEFINITIONS_H
