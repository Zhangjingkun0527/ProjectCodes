#include "definitions.h"
//计算函数运行时间的通用方法
template <typename T>
double time_count_for_function(T const &function);

template <typename T>
void swap(T const &a, T const &b){
    a ^= b ^= a ^= b;
}

void print_time_consumed(algorithm_type algorithmType){
    //生成原始随机数据
    auto origin_data = generator_random_numbers((int)COUNT_OF_RANDOM_NUMBERS, (int)LOWER_BOUND, (int)UPPER_BOUND);
    double time_consumed;

    auto index_of_end = ((int) COUNT_OF_RANDOM_NUMBERS) - 1;
    //根据指定的排序算法类型进行排序并计算时间
    auto function = [=]() -> void {
        switch (algorithmType){
            case INSERT_SORT: {
                printf("插入排序");
                return insert_sort(origin_data, 0, index_of_end);
            }

            case QUICK_SORT:{
                printf("普通快速排序");
                return general_quick_sort(origin_data, 0, index_of_end);
            }

            case OPTIMIZED_QUICK_SORT:{
                printf("优化快速排序%d(Threshold)", THRESHOLD);
                return optimized_quick_sort(origin_data, 0, index_of_end, THRESHOLD);
            }

            case MERGE_SORT:{
                printf("普通归并排序");
                return general_merge_sort(origin_data, 0, index_of_end);
            }

            case OPTIMIZED_MERGE_SORT:{
                printf("优化归并排序%d(Threshold)", THRESHOLD);
                return optimized_merge_sort(origin_data, 0, index_of_end, THRESHOLD);
            }

            case HEAP_SORT_USING_TERNARY_TREE: {
                printf("三叉树大顶堆排序");
                return heap_sort(origin_data, 0, index_of_end);
            }
        }
    };
    //计算并打印时间
    time_consumed = time_count_for_function(function);
    printf("算法在%dk级别数据下所花费时间为：%.0lfms\n", ((int)COUNT_OF_RANDOM_NUMBERS) / 1000, time_consumed);

    delete origin_data;
}

template <typename T>
double time_count_for_function(T const &function){
    clock_t  start, end;
    //计算函数运行时间
    start = clock();
    function();
    end = clock();

    auto time_consumed = (double)(end - start)/CLOCKS_PER_SEC * 1000;
    return time_consumed;
}