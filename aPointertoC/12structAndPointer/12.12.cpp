#include<stdio.h>
#include<stdlib.h>
#define MAX 10
typedef struct link {
	struct link* next;
	int num;
}l;
l* findNode(l* head,int num);
int main2() {
	l* q = (l*)malloc(MAX * sizeof(l));
	l* p = q;
	if ( q == NULL) {
		return 0;
	}
	for (int i = 0;i < MAX;i++) {
		//printf("%d\n", i);
		(q + i)->num = i;
		(q + i)->next = (q + i + 1);
		if (i == MAX - 1) {
		 (q+i)->next = NULL;
		}
	}

	l* r = findNode(p, 10);
	if (r == NULL) {
		printf("Î´ÕÒµ½\n");
	}
	else printf("%d\n", r->num);
	//for (int i = 0;i < MAX;i++) {
	//	printf("%d\n", (q + i)->num);
	//}
	/*while (p!= NULL) {
		printf("%d\n", p->num);
		p = p->next;
	 }*/
	free(q);

	return 0;
}
l* findNode(l* head, int num) {
	l* p=head;
	while (p != NULL) {
		if (p->num == num) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}