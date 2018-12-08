#include "definitions.h"

int main() {

    if(COUNT_OF_RANDOM_NUMBERS < 5e4){
        print_time_consumed(INSERT_SORT);
    }

    print_time_consumed(QUICK_SORT);
    print_time_consumed(OPTIMIZED_QUICK_SORT);
    print_time_consumed(MERGE_SORT);
    print_time_consumed(OPTIMIZED_MERGE_SORT);
    print_time_consumed(HEAP_SORT_USING_TERNARY_TREE);

    return 0;
}