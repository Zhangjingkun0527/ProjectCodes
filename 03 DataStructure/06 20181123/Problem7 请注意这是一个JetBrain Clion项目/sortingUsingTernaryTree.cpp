#include "definitions.h"
#define NO_CHILD -1
//�������е�����ȫ�������ĺ���
void adjustTree(vector<int> &origin, int index, int length);
//����vector�������±�λ�õ�����
void swap(vector<int> &origin, int index1, int index2);
//�ҵ��±�Ϊindex�Ľ������к����������Ǹ������±�
int findMax(vector<int> &origin, int index, int length);

void sorting(vector<int> &origin){
    if(origin.empty()) return;

    //������ʼ��
    int nums = origin.size();
    for(int i = nums / 3 - 1; i >= 0 ; i--){
        adjustTree(origin, i, nums);
    }
    //����n�δ󶥶ѣ��ҵ�ÿ�ε����������㣬���õ�����λ��
    for(int i = nums - 1; i > 0; i--){
        swap(origin, 0, i);
        adjustTree(origin, 0, i);
    }
}

void adjustTree(vector<int> &origin, int index, int length){

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

void swap(vector<int> &origin, int index1, int index2){
    origin[index1] ^= origin[index2] ^= origin[index1] ^= origin[index2];
}

int findMax(vector<int> &origin, int index, int length){
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