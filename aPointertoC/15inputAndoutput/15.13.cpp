#include<stdio.h>
#include<string.h>
#define MAX 5
int main3() {
	char str[MAX];
	int i = 0;
	int j = 0;
	//即使我输入变多了，标准函数只会以最大的数目读取，并输出
	//回车清空缓冲区后，
	//	内层循环仍然会判断剩余的字符串是否超限，
	//	理论上可以做到无限输入输出
	while (fgets(str, MAX, stdin) != NULL) {
		i++;
	printf("外层循环执行第%d次\n",i);
		fputs(str, stdout);
		while (strchr(str, '\n') == NULL) {
			j++;
			printf("内层循环执行第%d次\n", j);
			fgets(str, MAX, stdin);
			fputs(str, stdout);
		 
		 
		}

	}
	return 0;
}