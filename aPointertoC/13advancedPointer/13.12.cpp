#include<stdio.h>
#include<stdlib.h>
#define MAX 10
typedef struct link {
	struct link* next;
	int data;
}n;

//printdata即为回调函数，函数本身与普通函数并无任何区别
void printdata(n* node) {
	printf("%d\n", node->data);
}

//在另一函数中以回调函数指针为参数，调用了回调函数，名字由来
void begin(n* head, void (*func)(n* node)) {
	n* p = head;
	while (p!= NULL) {
		func(p);
		p = p->next;
	}
}

int main2() {
	n* a;
	a = (n*)malloc(MAX * sizeof(n));
	n* p = a;
	if (a == NULL) {
		return 0;
	}
	for (int i = 0;i < MAX;i++) {
		(a + i)->data = i;
		if (i == MAX - 1) {
			(a + i)->next = NULL;

		}
		else (a + i)->next = a + i + 1;
	 
	}
	begin(a, printdata);
	free(a);

	return 0;
}
