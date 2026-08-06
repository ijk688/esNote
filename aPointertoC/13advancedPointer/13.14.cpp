#include<stdio.h>
#include<stdlib.h>
#define MAX 10
int cmpChar(void* a, void* b);
int cmpInt(void* a, void* b);
void sort(void* arr, int num, size_t size, int (*func)(void* a, void* b));

int main4() {
 
	char array1[MAX];
	for (int i = 0;i < MAX;i++) {
		array1[i] = '0' + 9 - i;
		printf("%c ", array1[i]);
	}
	 
	sort(array1, MAX, sizeof(char), cmpChar);
	for (int i = 0;i < MAX;i++) {
		printf("%c ", array1[i]);
	}

	printf("\n");

	int array[MAX];
	for (int i = 0;i < MAX;i++) {
		array[i] = 10-i;
		printf("%d ", array[i]);
	}
	//此代码体现了回调函数的封装性
	//想要添加新类型是仅需修改增添回调函数
	// 不用修改sort函数中的任何内容！！！
	//仅仅在调用时将函数指针传入即可
	sort(array, MAX, sizeof(int), cmpInt);
	 
	for (int i = 0;i < MAX;i++) {
		printf("%d ", array[i]);
	}
	return 0;
}

int cmpChar(void* a, void* b) {
	if (*(char*)a > *(char*)b) {
		return 1;
	}
	else if (*(char*)a < *(char*)b) {
		return -1;
	}
	else return 0;
}
int cmpInt(void* a, void* b) {
	if (*(int*)a > *(int*)b) {
		return 1;
	}
	else if (*(int*)a < *(int*)b) {
		return -1;
	}
	else return 0;
}
void sort(void* arr,int num ,size_t size,int (*func)(void* a, void* b)) {
	int i = 0;
	int j = 0;
	for (i = 0;i < num - 1;i++) {
		for (j = i + 1;j < num;j++) {
			char* p = (char*)arr + i * size;
			char* q = (char*)arr + j * size;
			char t;
			if ((*func)(p,q)>0) {
				for (size_t k = 0;k < size;k++) {
				t = *(q + k);
				*(q+k) = *(p+k);
				*(p+k) = t;
				}		 
			}
		}
	}
}

