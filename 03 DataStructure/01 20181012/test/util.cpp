#include "test/test/pch.h"

//self defined print function for linked list.
void print(node *list){
	list = list->next;
	while(list != NULL){
		printf("%d ", list->data);
		list = list->next;
	}
	printf("\n");
}

//this function could generate all nodes and link them to a list from an array
void generateListFromArray(node *&list, int datas[], int size){
	list->next = (node *)malloc(sizeof(node));
	auto p = list->next;
	for (auto i = 0; i < size; i++){
		p->data = datas[i];
		if (i != size - 1){
			p->next = static_cast<node *>(malloc(sizeof(node)));
		} else {
			p->next = nullptr;
			return;
		}
		p = p->next;
	}
}
