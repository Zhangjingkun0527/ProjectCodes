#include "definitions.h"
//C�Դ����ŵıȽϺ���
int cmp(const void *a,const void *b);
void print_search_times_for_binary_search() {
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
    //�������������ʹ��C�Դ��Ŀ��ź������򣬴�С��������
    qsort(for_search_arr, static_cast<size_t>(count), sizeof(for_search_arr[0]), cmp);

    //��keys��ÿ��key��Ŀ������for_search_arr���м���������¼�����ܴ����ͼ����ɹ��Ĵ���
    for(int i = 0; i < count; i++) {
        if(binary_search(for_search_arr, keys[i], temp) != NOT_FOUND) {
            count_of_successful_search += 1;
        }
        count_of_search += temp;
        temp = 0;
    }


    printf("���ּ�������%dk�μ����ܴ���Ϊ%lld���ɹ������Ĵ���Ϊ%d�������ɹ��ٷֱ�Ϊ%.2f%%��ÿ�μ������е�ƽ���Ƚϴ���Ϊ%.2f��\n"
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
        //��ƥ�䵽keyʱֹͣѭ�������û��ƥ�䵽��Ӧ���ж��Ƿ��Ѿ�����begin����end�������������֣�Ӧ��ֹͣ
        if(arr[middle] == key) {
            ++count_of_search;
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
    return *(int *)a-*(int *)b;//���Ǵ�С�����������ǴӴ�С�ĳɣ� return *(int *)b-*(int *)a;
}
