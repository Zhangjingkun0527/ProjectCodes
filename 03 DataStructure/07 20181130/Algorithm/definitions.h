#ifndef ALGORITHM_DEFINITIONS_H
#define ALGORITHM_DEFINITIONS_H

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <functional>
using namespace std;

//随机数的数量，下界，上界，可以使用e表达式
#define COUNT_OF_RANDOM_NUMBERS 1e6
#define LOWER_BOUND 1
#define UPPER_BOUND 1e6

//优化排序所用到的门槛值
#define THRESHOLD 7

//定义要进行测试的函数类型，用于计算时间
enum algorithm_type{
    INSERT_SORT,
    QUICK_SORT,
    OPTIMIZED_QUICK_SORT,
    MERGE_SORT,
    OPTIMIZED_MERGE_SORT,
    HEAP_SORT_USING_TERNARY_TREE
};

/*
 * quick_sort的函数定义
 */

/*
 * 普通快速排序，未经优化
 */
void general_quick_sort(int *origin, int left, int right);

/*
 * 经Threshold优化的快速排序
 */
void optimized_quick_sort(int *origin, int left, int right, int threshold);


/*
 * merge_sort的函数定义
 */
/*
 * 未经优化的归并排序
 */
void general_merge_sort(int *origin, int left, int right);
/*
 * 经优化的归并排序
 */
void optimized_merge_sort(int *origin, int left, int right, int threshold);



/*
 *  heap_sort_using_ternary_tree的函数定义
 */
//三叉树堆排序
void heap_sort(int *origin, int begin, int end);

/*
 * random_number_generator的函数定义
 */

/*
 * 随机数生成函数，只生成整型Int范围内的随机数
 * @count 随机数的个数
 * @lower_bound 随机数下界
 * @upper_bound 随机数上界
 * @return 返回随机数数组的指针
 */
int *generator_random_numbers(int count, int lower_bound, int upper_bound);



/*
 * insert_sort的函数定义
 */
//插入排序
void insert_sort(int *origin, int begin, int end);



/*
 * util的函数定义
 */
//交换两个整型数的数值
template <typename T>
void swap(T const &a, T const &b);
//根据定义的排序算法类型，计算函数运行时间并打印出来
void print_time_consumed(algorithm_type algorithmType);

#endif //ALGORITHM_DEFINITIONS_H
