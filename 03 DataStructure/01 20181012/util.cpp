#include "headers.h"

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
void generateListFromArray(node *list, int datas[], int size){
	list->next = (node *)malloc(sizeof(node));
	node *p = list->next;
	for (int i = 0; i < size; i++){
		p->data = datas[i];
		if (i != size - 1){
			p->next = (node *)malloc(sizeof(node));
		} else {
			p->next = NULL;
			return;
		}
		
		p = p->next;
	}
}

//this function can remove the surplus nodes which have same data from a non-decreasing linked list
void removeSameData(node *head){
	node *pre = head->next;
	node *p = pre->next;
	while(p){
		if(p->data == pre->data){
			node *temp;
			temp = p;
			p = p->next;
			pre->next = p;
			free(temp);
		}else{
			pre = pre->next;
			p = p->next;	
		}
	}
}
