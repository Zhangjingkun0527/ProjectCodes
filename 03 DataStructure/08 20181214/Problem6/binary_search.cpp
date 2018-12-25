#include "definitions.h"

int binary_search(int *arr, int key, int count, int begin, int end){
    int middle = (begin + end) / 2;
    auto is_key_found = false;
    while(true) {
        //当匹配到key时停止循环，如果没有匹配到，应当判断是否已经出现begin大于end的情况，如果出现，应当停止
        if(arr[middle] == key) {
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
    }

    if(is_key_found) {
        return middle;
    } else {
        return NOT_FOUND;
    }
}

int binary_search_for_two_dimension_array(int **arr, int key, int begin, int end, int index) {
    int middle = (begin + end) / 2;
    auto is_key_found = false;
    while(true) {
        //当匹配到key时停止循环，如果没有匹配到，应当判断是否已经出现begin大于end的情况，如果出现，应当停止
        if(arr[middle][index] == key) {
            is_key_found = true;
            break;
        } else if(begin > end) break;
        //如果当前值小于key，就代表key在middle的右边，反之在左边
        if(arr[middle][index] < key) {
            begin = middle + 1;
        } else {
            end = middle - 1;
        }
        middle = (begin + end) / 2;
    }

    if(is_key_found) {
        return middle;
    } else {
        return NOT_FOUND;
    }
}