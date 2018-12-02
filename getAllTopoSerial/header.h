#ifndef _HEADER_H_
#define _HEADER_H_
#include <vector>
#include <list>

	extern bool visited[];
	extern int data[][100];
	int NumberOfNodes(/*int **data,*/ int v, int **restore, int order);
	int DeleteEdges(/*int **data,*/ int v, std::list<std::pair<int,int> > *tmp, int first);
	int RevertEdges(/*int **data,*/ int v, std::list<std::pair<int,int> > *tmp, int first);
	int TopologicSequence(/*int **data,*/ int v);

#endif
