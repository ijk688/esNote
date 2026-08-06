#include<stdio.h>
#include<stdlib.h>
#define MAX 10
void* calloc(size_t num_elements, size_t element_size);
//void* malloc(size_t size);
//void free(void* p);
int main1() {
	//char* st = (char*)calloc(MAX, sizeof(char));
	int* arr = (int*)calloc(MAX, sizeof(int));
	int num = MAX;
	while (num--) {
		printf("%d\n", *arr);
		arr++;
	}
	free(arr);
	return 0;
	//char* str = (char *)malloc(MAX * sizeof(char));
	//if (str != NULL) {
	//	char* nstr = str;
	//	for (int i = 0;i < 5;i++) {
	//		*nstr = '0' + i;
	//		printf("%c\n", *nstr);
	//		nstr++;
	//	}
	//	*nstr = '\0';
	//	printf("%s\n", str);
	//	free(str);
 //
	//	return 0;
	//}
	 
}
void* calloc(size_t num_elements, size_t element_size) {
	size_t totalnum = num_elements * element_size;
	void* p = malloc(totalnum);
	if (p == NULL) {
		return NULL;
	}
	char* q = (char*)p;
	while (totalnum--) {
		*q++=0;
	}
	return p;

}