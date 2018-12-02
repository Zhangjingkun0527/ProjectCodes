#include "header.h"
#include <stdio.h>
#include <stdlib.h>

 bool visited[100];
 int data[100][100];

int TopologicSequence(/*int **data,*/ int v)
{
	FILE *file = fopen("C:\\Users\\Administrator\\Desktop\\answer.txt", "a");
	std::list<std::pair<int,int> > edges;
	int **restore;
	restore = new int *[v];
	int i,j,sum = 0;
	for(i = 0; i < v; i++)
		restore[i] = NULL;
	int *len = new int[v];  //记录各步前驱节点的个数
	int *index = new int[v]; //记录各步的索引
	int *result = new int[v];
	for(i = 0; i < v; i++)
	{
		len[i] = index[i] = 0;
		result[i] = -1;
	}
	//获取第一批无直接前驱头节点

	int n = NumberOfNodes(/*data,*/ v, restore, 0);
	len[0] = n;
	index[0] = 0;
	i = 0;
	while(i >= 0)
	{
		if(i < v)
		{
			//if and only if there is another value
			if(index[i] < len[i])
			{
				result[i] = restore[i][ index[i]++ ];
				DeleteEdges(/*data,*/ v, &edges, result[i]);
				int tmp = NumberOfNodes(v, restore, ++i);
				if(i < v)
				{
					len[i] = tmp;
					index[i] = 0;
				}
				else
				{
					RevertEdges(v, &edges, result[i - 1]);
				}
			}
			else
			{
				i--;
				if(i >= 0)
				{
					int tmp = restore[i][index[i] - 1];
					RevertEdges(v, &edges, tmp);
				}
			}
		}
		else  //得到一个解
		{
			sum++;
			int tmp = 0;
			 //将插入位置定位在文件末尾 
    		fseek(file, 0, SEEK_END);
			while(tmp < v) fprintf(file ,"%d  ", result[tmp++]);
			fseek(file, 0, SEEK_END);
			fprintf(file, "\n");
			//printf("\n-----------------------------\n");
			i--;
		}
	}

	delete index;
	delete len;
	delete result;
	for(i = 0; i < v; i++)
	{
		if(restore[i]) delete restore[i];
	}
	delete[] restore;
	return sum;
}

int NumberOfNodes(/*int **data,*/ int v, int **restore, int order)
{
	if(order >= v) return 0;
	int i,j;
	int sum = 0;
	int *tmp = new int[v];
	for(j = 0; j < v; j++)
	{
		if(!visited[j])
		{
			for(i = 0; i < v; i++)
			{
				if(data[i][j] == 1) break;
			}
			if( i == v)
			{
				tmp[sum++] = j;
			}
		}
	}
	if(sum > 0)
	{
		restore[order] = tmp;
	}
	else
	{
		delete tmp;
		if(restore[order])
		{
			delete restore[order];
			restore[order] = NULL;
		}
	}
	return sum;
}

int DeleteEdges(/*int **data,*/ int v, std::list<std::pair<int,int> > *tmp, int first)
{
	int i;
	int sum = 0;
	for(i = 0; i < v; i++)
	{
		if(data[first][i] == 1)
		{
			tmp->push_back(std::pair<int,int>(first, i));
			data[first][i] = 0;
			sum++;
		}
	}
	visited[first] = true;
	return sum;
}

int RevertEdges(/*int **data,*/ int v, std::list<std::pair<int,int> > *tmp, int first)
{
	int sum = 0;
	int i;
	std::pair<int, int> t;
	std::list<std::pair<int,int> > kkk;
	std::list<std::pair<int, int> >::iterator itr = tmp->begin();
	std::list<std::pair<int, int> >::iterator tmp_itr;
	kkk.clear();
	while(itr != tmp->end())
	{
		t = *itr;
		if(t.first == first)
		{
			data[first][t.second] = 1;
			//tmp->erase(tmp_itr);    //it will not affect the itr iterator
			sum++;
		}
		else
		{
			kkk.push_back(t);
		}

		++itr;
	}
	visited[first] = false;
	tmp->clear();
	itr = kkk.begin();
	while(itr != kkk.end())
	{
		tmp->push_back(*itr);
		++itr;
	}
	return sum;
}
