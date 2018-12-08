#include "definitions.h"
//���㺯������ʱ���ͨ�÷���
template <typename T>
double time_count_for_function(T const &function);

template <typename T>
void swap(T const &a, T const &b){
    a ^= b ^= a ^= b;
}

void print_time_consumed(algorithm_type algorithmType){
    //����ԭʼ�������
    auto origin_data = generator_random_numbers((int)COUNT_OF_RANDOM_NUMBERS, (int)LOWER_BOUND, (int)UPPER_BOUND);
    double time_consumed;

    auto index_of_end = ((int) COUNT_OF_RANDOM_NUMBERS) - 1;
    //����ָ���������㷨���ͽ������򲢼���ʱ��
    auto function = [=]() -> void {
        switch (algorithmType){
            case INSERT_SORT: {
                printf("��������");
                return insert_sort(origin_data, 0, index_of_end);
            }

            case QUICK_SORT:{
                printf("��ͨ��������");
                return general_quick_sort(origin_data, 0, index_of_end);
            }

            case OPTIMIZED_QUICK_SORT:{
                printf("�Ż���������%d(Threshold)", THRESHOLD);
                return optimized_quick_sort(origin_data, 0, index_of_end, THRESHOLD);
            }

            case MERGE_SORT:{
                printf("��ͨ�鲢����");
                return general_merge_sort(origin_data, 0, index_of_end);
            }

            case OPTIMIZED_MERGE_SORT:{
                printf("�Ż��鲢����%d(Threshold)", THRESHOLD);
                return optimized_merge_sort(origin_data, 0, index_of_end, THRESHOLD);
            }

            case HEAP_SORT_USING_TERNARY_TREE: {
                printf("�������󶥶�����");
                return heap_sort(origin_data, 0, index_of_end);
            }
        }
    };
    //���㲢��ӡʱ��
    time_consumed = time_count_for_function(function);
    printf("�㷨��%dk����������������ʱ��Ϊ��%.0lfms\n", ((int)COUNT_OF_RANDOM_NUMBERS) / 1000, time_consumed);

    delete origin_data;
}

template <typename T>
double time_count_for_function(T const &function){
    clock_t  start, end;
    //���㺯������ʱ��
    start = clock();
    function();
    end = clock();

    auto time_consumed = (double)(end - start)/CLOCKS_PER_SEC * 1000;
    return time_consumed;
}