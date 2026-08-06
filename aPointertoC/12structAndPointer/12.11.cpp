#include<stdio.h>
#include<stdlib.h>
#define MAX 50
int num = 0;
typedef struct link{
	struct link* next;
}l;
int countnum(l* head);
int main1() {

	l* a = (l*)malloc(sizeof(l));
	l* b = (l*)malloc(sizeof(l));
	l* head=(l*)malloc(sizeof(l));
	head->next = a;
	a->next = b;
	b->next = NULL;
	printf("%d",countnum(head));
	free(head);
	return 0;
}
int countnum(l* head) {
	if (head->next == NULL) {
		return num;
	}
	else {
		return countnum(head->next)+1;
	}
}
//void countnum(l* head) {
//	if ((*head).next != NULL) {
//		num++;
//		countnum(head->next);
//	}
//	else {
//		printf("%d\n", num);
//	}
//}