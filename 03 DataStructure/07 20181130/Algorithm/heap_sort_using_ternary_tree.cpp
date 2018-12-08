#include "definitions.h"
#define NO_CHILD -1
//堆排序中调整完全三叉树的函数
void adjustTree(int *origin, int index, int length);
//找到下标为index的结点的所有孩子中最大的那个结点的下标
int findMax(int *origin, int index, int length);

void heap_sort(int *origin, int begin, int end){
    //建立初始堆
    int nums = end - begin + 1;
    for(int i = nums / 3 - 1; i >= 0 ; i--){
        adjustTree(origin, i, nums);
    }
    //调整n次大顶堆，找到每次调整后的最大结点，放置到最终位置
    for(int i = nums - 1; i > 0; i--){
        swap(origin[0], origin[i]);
        adjustTree(origin, 0, i);
    }
}

void adjustTree(int *origin, int index, int length){

    //首先暂存index位置的结点值
    int temp = origin[index];
    int tempIndex = index;
    //从当前结点的左孩子开始，依次调整
    for(int i = 3 * index + 1; i < length;){
        //寻找当前结点孩子中哪个孩子值最大，找到它的下标
        int maxChild = findMax(origin, i, length);
        //遇到叶结点直接结束
        if(maxChild == NO_CHILD) break;
        //如果这个孩子的值比父结点值大，那么把它拿到父结点位置上来
        //并将i和tempIndex指向这个最大孩子
        //i指向这个孩子是为了找到这个孩子结点的孩子结点的最大孩子结点，tempIndex则是往下寻找看有没有比temp更大的
        if(origin[maxChild] > temp){
            origin[tempIndex] = origin[maxChild];
            tempIndex = maxChild;
            i = 3 * maxChild + 1;
        }else break;
    }
    origin[tempIndex] = temp;
}

int findMax(int *origin, int index, int length){
    //左孩子
    int leftChild = index;
    //中孩子
    int middleChild = index + 1;
    //右孩子
    int rightChild = index + 2;

    //如果当前结点在length范围内没有孩子，返回-1
    if(leftChild >= length) return NO_CHILD;
    //如果当前结点只有左孩子，直接返回左孩子
    if(middleChild >= length) return leftChild;
    //如果当前结点只有左孩子和中孩子，那么比较两者大小
    else if(rightChild >= length){
        if(origin[leftChild] > origin[middleChild]) return leftChild;
        else return middleChild;
    }else{
        //对于三个孩子都存在的，从中找出最大的即可
        if(origin[leftChild] > origin[middleChild]){
            if(origin[leftChild] > origin[rightChild])
                return leftChild;
            else return rightChild;
        }else if(origin[middleChild] < origin[rightChild]){
            return rightChild;
        }else return middleChild;
    }
}