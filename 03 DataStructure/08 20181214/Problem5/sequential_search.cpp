#include "definitions.h"

void print_search_times_for_sequential_search() {
    //�������ڲ��ҵ��������
    auto upper_bound = static_cast<int>(UPPER_BOUND);
    auto lower_bound = static_cast<int>(LOWER_BOUND);
    auto count = static_cast<int>(COUNT_OF_RANDOM_NUMBERS);
    auto for_search_arr = generator_random_numbers(count, lower_bound, upper_bound);

    //����key���ڵ��������
    auto keys = generator_random_numbers(count, lower_bound, upper_bound);
    //�����ܴ���
    long long count_of_search = 0;
    //�����ɹ��ܴ���
    auto count_of_successful_search = 0;
    //���ڼ�¼ÿ�εļ�������
    long long temp = 0;
    //��keys��ÿ��key��Ŀ������for_search_arr���м���������¼�����ܴ����ͼ����ɹ��Ĵ���
    for(int i = 0; i < count; i++) {
        if(sequential_search(for_search_arr, keys[i], temp) != NOT_FOUND) {
            count_of_successful_search += 1;
        }
        count_of_search += temp;
    }

    printf("˳���������%dk�μ����ܴ���Ϊ%lld���ɹ������Ĵ���Ϊ%d�������ɹ��ٷֱ�Ϊ%.2f%%��ÿ�μ������е�ƽ���Ƚϴ���Ϊ%.2f��\n"
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
