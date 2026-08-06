#include<stdio.h>
#define MAX 10
int add(int a, int b) {
	return a + b;
}
int sub(int a, int b) {
	return a-b;
}
int func1();//返回类型为int的函数
int* func2();//返回类型为int指针的函数；
int* (*func3)();//返回类型为int指针的函数指针，func3为指针变量
int  (*func4[MAX])();//函数指针数组
int** (*fun5[MAX])();//函数指针数组，返回类型为二级指针
int** (**fun5[MAX])();


int main() {
	int (*func[MAX])(int,int) = { add,sub};
	printf("%d\n", func[0](3,5));
	printf("%d\n", func[1](3, 5));
	return 0;
}