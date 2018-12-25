#include "definitions.h"

void print_search_times_for_sequential_search() {
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
    //对keys中每个key在目标数组for_search_arr进行检索，并记录检索总次数和检索成功的次数
    for(int i = 0; i < count; i++) {
        if(sequential_search(for_search_arr, keys[i], temp) != NOT_FOUND) {
            count_of_successful_search += 1;
        }
        count_of_search += temp;
    }

    printf("顺序检索进行%dk次检索总次数为%lld，成功检索的次数为%d，检索成功百分比为%.2f%%，每次检索进行的平均比较次数为%.2f。\n"
            , static_cast<int>(COUNT_OF_RANDOM_NUMBERS / 1000),
            count_of_search,
            count_of_successful_search,
            count_of_successful_search * 100 / COUNT_OF_RANDOM_NUMBERS,
            count_of_search / COUNT_OF_RANDOM_NUMBERS);

}

int sequential_search(int *arr, int key, long long &count_of_search){
    auto max = static_cast<int>(COUNT_OF_RANDOM_NUMBERS);
    auto is_key_found = false;
    int i = 0;
    for(i = 0; i < max; i++) {
        if (arr[i] != key) continue;
        is_key_found = true;
        break;
    }

    if(is_key_found) {
        count_of_search = i + 1;
        return i;
    } else {
        count_of_search = max;
        return NOT_FOUND;
    }
}
