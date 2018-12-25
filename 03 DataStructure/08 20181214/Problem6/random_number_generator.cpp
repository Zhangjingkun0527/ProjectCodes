#include "definitions.h"

int *generator_random_numbers(int count, int lower_bound, int upper_bound){
    auto result = static_cast<int *>(malloc(sizeof(int) * count));
    for (auto i = 0; i < count; ++i) {
        //生成[lower_bound, upper_bound]之间的随机数
        auto temp = (rand() % (upper_bound - lower_bound + 1))+ lower_bound;
        result[i] = temp;
    }

    return result;
}