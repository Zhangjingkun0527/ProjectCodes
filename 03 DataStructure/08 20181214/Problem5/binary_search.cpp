#include "definitions.h"
//C自带快排的比较函数
int cmp(const void *a,const void *b);
void print_search_times_for_binary_search() {
    //生成用于查找的随机数组
    auto upper_bound = static_cast<int>(UPPER_BOUND);
    auto lower_bound = static_cast<int>(LOWER_BOUND);
    auto count = static_cast<int>(COUNT_OF_RANDOM_NUMBERS);
    auto for_search_arr = generator_random_numbers(count, lower_bound, upper_bound);

    //生成key所在的随机数组
    auto keys = generator_random_numbers(count, lower_bound, upper_bound);
    //检索总次数
    long long count_of_search = 0;
    //检索成功总次数
    auto count_of_successful_search = 0;
    //用于记录每次的检索次数
    long long temp = 0;
    //对数组进行排序，使用C自带的快排函数排序，从小到大排序
    qsort(for_search_arr, static_cast<size_t>(count), sizeof(for_search_arr[0]), cmp);

    //对keys中每个key在目标数组for_search_arr进行检索，并记录检索总次数和检索成功的次数
    for(int i = 0; i < count; i++) {
        if(binary_search(for_search_arr, keys[i], temp) != NOT_FOUND) {
            count_of_successful_search += 1;
        }
        count_of_search += temp;
        temp = 0;
    }


    printf("二分检索进行%dk次检索总次数为%lld，成功检索的次数为%d，检索成功百分比为%.2f%%，每次检索进行的平均比较次数为%.2f。\n"
            , static_cast<int>(COUNT_OF_RANDOM_NUMBERS / 1000),
           count_of_search,
           count_of_successful_search,
           count_of_successful_search * 100 / COUNT_OF_RANDOM_NUMBERS,
           count_of_search / COUNT_OF_RANDOM_NUMBERS);

}

int binary_search(int *arr, int key, long long &count_of_search){
    auto begin = 0;
    auto end = (static_cast<int>(COUNT_OF_RANDOM_NUMBERS)) - 1;
    int middle = (begin + end) / 2;
    auto is_key_found = false;
    while(true) {
        //当匹配到key时停止循环，如果没有匹配到，应当判断是否已经出现begin大于end的情况，如果出现，应当停止
        if(arr[middle] == key) {
            ++count_of_search;
            is_key_found = true;
            break;
        } else if(begin > end) break;
        //如果当前值小于key，就代表key在middle的右边，反之在左边
        if(arr[middle] < key) {
            begin = middle + 1;
        } else {
            end = middle - 1;
        }
        middle = (begin + end) / 2;
        ++count_of_search;
    }

    if(is_key_found) {
        return middle;
    } else {
        return NOT_FOUND;
    }
}

int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;//这是从小到大排序，若是从大到小改成： return *(int *)b-*(int *)a;
}
