#include<stdio.h>
#include<stdlib.h>
#define MAX 50
int main2() {
 
	int* arr = (int*)malloc(MAX * sizeof(int));
	if (arr != NULL) {
		int num;
		int inum;
		int i = 0;
		scanf_s("%d", &num);
		while (i < num) {
			scanf_s("%d", &inum);
			if (inum == -1) {
				break;
			}
			arr[i] = inum;
			i++;
			printf("循环执行第%d次\n", i);
		}
	/*	while ((scanf_s("%d", &inum) != EOF)&&i<num) {
			arr[i] = inum;
			i++;
			printf("循环执行第%d次\n", i);
		}*/
		for (int j = 0;j < i;j++) {
		
			printf("%d\n", arr[j]);
		}
		free(arr);
	}
	 

	return 0;
}