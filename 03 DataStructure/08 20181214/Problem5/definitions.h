#ifndef ALGORITHM_DEFINITIONS_H
#define ALGORITHM_DEFINITIONS_H

#include <cstdio>
#include <stdlib.h>

//��������������½磬�Ͻ磬����ʹ��e���ʽ
#define COUNT_OF_RANDOM_NUMBERS 3e4
#define LOWER_BOUND 1
#define UPPER_BOUND 3e4

#define NOT_FOUND -1

/**
 * ��������ɺ�����ֻ��������Int��Χ�ڵ������
 * @param count ������ĸ���
 * @param lower_bound ������½�
 * @param upper_bound ������Ͻ�
 * @return ��������������ָ��
 */
int *generator_random_numbers(int count, int lower_bound, int upper_bound);

/**
 * ˳�����
 * @param arr ��������
 * @param key ��������ֵ
 * @param count_of_search
 * @return ���ҽ�������û���ҵ��򷵻�-1������ҵ��򷵻��±�
 */
int sequential_search(int *arr, int key, long long &count_of_search);

/**
 * ��ӡ˳����������ܴ��������ҳɹ����������ҳɹ��ٷֱȵ���ĿҪ�������
 */
void print_search_times_for_sequential_search();


/**
 * ���ּ���
 * @param arr ��������
 * @param key ��������ֵ
 * @param count_of_search
 * @return ���ҽ�������û���ҵ��򷵻�-1������ҵ��򷵻��±�
 */
int binary_search(int *arr, int key, long long &count_of_search);

/**
 * ��ӡ˳����������ܴ��������ҳɹ����������ҳɹ��ٷֱȵ���ĿҪ�������
 */
void print_search_times_for_binary_search();

#endif //ALGORITHM_DEFINITIONS_H
