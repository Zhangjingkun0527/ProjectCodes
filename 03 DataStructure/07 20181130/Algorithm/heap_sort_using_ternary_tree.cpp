#include "definitions.h"
#define NO_CHILD -1
//�������е�����ȫ�������ĺ���
void adjustTree(int *origin, int index, int length);
//�ҵ��±�Ϊindex�Ľ������к����������Ǹ������±�
int findMax(int *origin, int index, int length);

void heap_sort(int *origin, int begin, int end){
    //������ʼ��
    int nums = end - begin + 1;
    for(int i = nums / 3 - 1; i >= 0 ; i--){
        adjustTree(origin, i, nums);
    }
    //����n�δ󶥶ѣ��ҵ�ÿ�ε����������㣬���õ�����λ��
    for(int i = nums - 1; i > 0; i--){
        swap(origin[0], origin[i]);
        adjustTree(origin, 0, i);
    }
}

void adjustTree(int *origin, int index, int length){

    //�����ݴ�indexλ�õĽ��ֵ
    int temp = origin[index];
    int tempIndex = index;
    //�ӵ�ǰ�������ӿ�ʼ�����ε���
    for(int i = 3 * index + 1; i < length;){
        //Ѱ�ҵ�ǰ��㺢�����ĸ�����ֵ����ҵ������±�
        int maxChild = findMax(origin, i, length);
        //����Ҷ���ֱ�ӽ���
        if(maxChild == NO_CHILD) break;
        //���������ӵ�ֵ�ȸ����ֵ����ô�����õ������λ������
        //����i��tempIndexָ����������
        //iָ�����������Ϊ���ҵ�������ӽ��ĺ��ӽ�������ӽ�㣬tempIndex��������Ѱ�ҿ���û�б�temp�����
        if(origin[maxChild] > temp){
            origin[tempIndex] = origin[maxChild];
            tempIndex = maxChild;
            i = 3 * maxChild + 1;
        }else break;
    }
    origin[tempIndex] = temp;
}

int findMax(int *origin, int index, int length){
    //����
    int leftChild = index;
    //�к���
    int middleChild = index + 1;
    //�Һ���
    int rightChild = index + 2;

    //�����ǰ�����length��Χ��û�к��ӣ�����-1
    if(leftChild >= length) return NO_CHILD;
    //�����ǰ���ֻ�����ӣ�ֱ�ӷ�������
    if(middleChild >= length) return leftChild;
    //�����ǰ���ֻ�����Ӻ��к��ӣ���ô�Ƚ����ߴ�С
    else if(rightChild >= length){
        if(origin[leftChild] > origin[middleChild]) return leftChild;
        else return middleChild;
    }else{
        //�����������Ӷ����ڵģ������ҳ����ļ���
        if(origin[leftChild] > origin[middleChild]){
            if(origin[leftChild] > origin[rightChild])
                return leftChild;
            else return rightChild;
        }else if(origin[middleChild] < origin[rightChild]){
            return rightChild;
        }else return middleChild;
    }
}