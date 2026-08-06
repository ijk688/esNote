#include<stdio.h>
#include<stdlib.h>
#define MAX 10
typedef struct Node {
	struct Node* fwd;
	struct Node* bwd;
	int data;
}n;
//int dll_insert(n* head, n* end,int value);
int main() {
	n* head = (n*)malloc(MAX * sizeof(n));
	n* p = head;
	if (head == NULL) {
		return 0;
	}
	if (p == NULL) {
		printf("pÎª¿Õ\n");
		return 0;
	}
	for (int i = 0;i < MAX;i++) {
		(head + i)->data = i;
		if(i<MAX-1) (head + i)->fwd = head + i + 1;
		else 	(head + i)->fwd = NULL;
		if(i>0) (head + i)->bwd = head + i - 1;
		else     head->bwd = NULL;
	}
	//for (int i = 0;i < MAX;i++) {
	//	(head + i)->data = i;
	//	if (i == 0) {
	//		(head + i)->fwd = (head + i + 1);
	//		head->bwd = NULL;
	//		continue;
	//	}
	//	else if (i == MAX - 1) {
	//		(head+i)->fwd = NULL;
	//		(head + i)->bwd = (head + i - 1);
	//		continue;
	//	}
	//	else {
	//		(head + i)->fwd = (head + i + 1);
	//		(head + i)->bwd = (head + i - 1);
	//	}
	//	 
	//}
	 
	//printf("%d\n", p->data);
	//printf("%d\n", (p->fwd)->data);
	n* last=head;
	while (p != NULL) {
		printf("fwd:%d\n", p->data);
		last = p;
		p = p->fwd;
	}
	p = last;
	while (p != NULL) {
		printf("bwd:%d\n", p->data);
		p = p->bwd;
	}
	free(head);
	return 0;
}
//int dll_insert(n* head, n* end,int value) {
//
//}