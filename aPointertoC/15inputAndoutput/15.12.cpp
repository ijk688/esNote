#include<stdio.h>
#define MAX 100
int main2() {
	char str[MAX];
	while (fgets(str, MAX, stdin) != NULL) {
		fputs(str, stdout);
	}
	/*然后就是此程序循环条件的解释，条件判断为空，
	即为fgets函数并未读取到任何字符返回空指针，
	这应该是内部函数所返回的，
	当然返回空指针条件显然易见就是函数内部代码条件判断出我输入了EOF，
	所以即使我不知道内部函数究竟是什么细节，
	我也能根据我的输入以及函数使用特点推断出*/
	while (fgets(str, MAX, stdin)!= NULL) {
		fputs(str,stdout);
	}
	return 0;
}