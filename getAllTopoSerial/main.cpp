
#include "header.h"
#include <stdlib.h>
#include <stdio.h>

//global bool visied[];
//global int data[][];

int main(int argc, char *argv[])
{
	int i,first, second, num, edges;

	for(first = 0; first < 100; first++)
	{
		visited[first] = false;
		for(second = 0; second < 100; second++)
			data[first][second] = 0;
	}
	num = 9;
	edges = 10;
	/*fputs("Input vertex numbers:", stdout);
	scanf("%d",&num);
	fputs("Input edges numbers:", stdout);
	scanf("%d", &edges);*/
	int buf[20] = {
		/*0,7, 7,8, 8,6, 0,2, 2,3, 3,6, 1,2, 1,3, 1,4, 3,5, 4,5*/
		0,1, 1,3, 3,6, 3,2, 6,5, 8,6, 8,7, 5,4, 2,4, 7,5
	};
	for(i = 0; i < 20; i++)
	{
		first = buf[i];
		second = buf[++i];
		data[first][second] = 1;
	}
	/*for(i = 0; i < edges; i++)
	{
		fputs("Input two vertex:", stdout);
		scanf("%d%d", &first, &second);
		data[first][second] = 1;
	}*/
	int tmp = TopologicSequence(num);
	printf("\nThere are %d solutions!", tmp);
	getchar();

}
