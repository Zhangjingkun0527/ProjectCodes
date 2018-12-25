#include "definitions.h"

int binary_search(int *arr, int key, int count, int begin, int end){
    int middle = (begin + end) / 2;
    auto is_key_found = false;
    while(true) {
        //��ƥ�䵽keyʱֹͣѭ�������û��ƥ�䵽��Ӧ���ж��Ƿ��Ѿ�����begin����end�������������֣�Ӧ��ֹͣ
        if(arr[middle] == key) {
            is_key_found = true;
            break;
        } else if(begin > end) break;
        //�����ǰֵС��key���ʹ���key��middle���ұߣ���֮�����
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
        //��ƥ�䵽keyʱֹͣѭ�������û��ƥ�䵽��Ӧ���ж��Ƿ��Ѿ�����begin����end�������������֣�Ӧ��ֹͣ
        if(arr[middle][index] == key) {
            is_key_found = true;
            break;
        } else if(begin > end) break;
        //�����ǰֵС��key���ʹ���key��middle���ұߣ���֮�����
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