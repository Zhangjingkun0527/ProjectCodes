#include "headers.h" 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void print(node *list);
int main(int argc, char** argv) {

	node *first = (node *)malloc(sizeof(node));
	node *second = (node *)malloc(sizeof(node));
	int i = 0;
	node *p = (node *)malloc(sizeof(node));
	node *q = (node *)malloc(sizeof(node));
	first->next = p;
	second->next = q;
	int critical = 20;
	while(i < critical){
		if(i % 2 != 0){
			p->data = i;
			if(i + 1 != critical){
				p->next = (node *)malloc(sizeof(node));	
				p = p->next;
			}else p->next = NULL;
		}else{
			q->data = i;
			if(i + 2 != critical){
				q->next = (node *)malloc(sizeof(node));
				q = q->next;	
			}else q->next = NULL;	
		}
		i++;
	}
	
	//jointTwoLinkedLists(first, second);
	//print(first);
	
	//node *result = findMaxNode(first);
	//printf("%d", result->data);
	
	//invertTheLinkedList(first);
	//print(first);
	
	print(first);
	deleteAllSpecifiedNodes(first, 3, 15);
	print(first);
	
	system("pause");
	return 0;
}

void print(node *list){
	list = list->next;
	while(list != NULL){
		printf("%d ", list->data);
		list = list->next;
	}
	printf("\n");
}

