#include "definitions.h"

int main() {

    auto count = 6;
    int array[] = {1,3,6,3,1,2};//{1,1,2,5,6,3,5,8,1,3,4,6,5,4,8,4,5};//generator_random_numbers(count, 1, 10000);
    auto K = 5;

    if(question_1(array, count, K)) {
        printf("n^2算法在目标数组中找到2个数，它们的和等于%d。\n", K);
    } else {
        printf("在目标数组中没有2个数，使得它们的和等于%d。\n", K);
    }

    if(question_2(array, count, K)) {
        printf("n log n算法在目标数组中找到2个数，它们的和等于%d。\n", K);
    } else {
        printf("在目标数组中没有2个数，使得它们的和等于%d。\n", K);
    }

    if(question_3(array, count, K)) {
        printf("n^2算法在目标数组中找到3个数，它们的和等于%d。\n", K);
    } else {
        printf("在目标数组中没有3个数，使得它们的和等于%d。\n", K);
    }

    if(question_4(array, count, K)) {
        printf("n^2 log n在目标数组中找到4个数，它们的和等于%d。\n", K);
    } else {
        printf("在目标数组中没有4个数，使得它们的和等于%d。\n", K);
    }

    return 0;
}