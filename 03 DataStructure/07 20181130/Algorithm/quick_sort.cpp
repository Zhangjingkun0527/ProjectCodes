#include "definitions.h"
//快速排序中子序列的排序函数
int quick_sort_swap_function(int *origin, int left, int right);
/*
 * 普通快速排序，未经优化
 */
void general_quick_sort(int *origin, int left, int right){
    if(right <= left) return;

    //选择当前序列的轴值
    auto index_of_pivot = (left + right) / 2;
    //将轴值放在子序列最左端，将最左端的放在轴值位置，为了方便交换
    swap(origin[left], origin[index_of_pivot]);
    //根据轴值对当前序列进行调整，得到轴值最后所在的位置
    auto pivot = quick_sort_swap_function(origin, left, right);

    //对轴值两端的子序列进行同样的操作
    general_quick_sort(origin, left, pivot - 1);
    general_quick_sort(origin, pivot + 1, right);
}

/*
 * 经Threshold优化的快速排序
 */
void optimized_quick_sort(int *origin, int left, int right, int threshold){
    if(right - left + 1 > threshold){
        //选择当前序列的轴值
        auto index_of_pivot = (left + right) / 2;
        //将轴值放在子序列最左端，将最左端的放在轴值位置，为了方便交换
        swap(origin[left], origin[index_of_pivot]);
        //根据轴值对当前序列进行调整，得到轴值最后所在的位置
        auto pivot = quick_sort_swap_function(origin, left, right);

        //对轴值两端的子序列进行同样的操作
        optimized_quick_sort(origin, left, pivot - 1, threshold);
        optimized_quick_sort(origin, pivot + 1, right, threshold);
    }else insert_sort(origin, left, right);
}

int quick_sort_swap_function(int *origin, int left, int right){
    int i = left, j = right;
    //暂存轴值
    int pivot = origin[left];
    while (i != j){
        //先从子序列最右边开始扫描
        while (origin[j] >= pivot && i < j) --j;
        if(i < j){
            //遇到小于轴值的放在左边，i指针+1
            origin[i] = origin[j];
            ++i;
        }

        //再从子序列左端开始扫描
        while (origin[i] <= pivot && i < j) ++i;
        if(i < j){
            //遇到大于轴值的放在右边，j指针-1
            origin[j] = origin[i];
            --j;
        }
    }
    //结束后，置放轴值
    origin[i] = pivot;
    //返回分隔点
    return i;
}