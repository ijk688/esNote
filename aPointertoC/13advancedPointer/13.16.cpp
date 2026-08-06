#include<stdio.h>
#define MAX 50
char** do_args(int argc, char** argv, char* control,
	void (*do_arg)(int ch, char* value),
	void (*illegal_arg)(int ch));
void do_arg(int ch, char* value);
void illegal_arg(int ch);
int main6(int argc, char** argv) {
	char rule[MAX] = "hvf+jasdhad+asldhfnnn";
	char** res = do_args(argc, argv, rule, do_arg, illegal_arg);

	printf("解析完成剩余参数：\n");
	while (*res) {
		printf("结果为：%s\n", *res);
		res++;
	}
	return 0;
}

void do_arg(int ch, char* value) {
	printf("回调do_arg\n");
	printf("合法参数: -%c\n", ch);
	if (value) {
		printf("  参数值: %s\n", value);
	}
}

void illegal_arg(int ch) {
	printf("回调illegal_arg\n");
	printf("非法参数: -%c\n", ch);
}

char** do_args(int argc, char** argv, char* control,
	void (*do_arg)(int ch, char* value),
	void (*illegal_arg)(int ch)) {
	/*跳过程序名参数*/
	if (*(argv + 1) == NULL) {
		return argv;
	}
	char** p = argv + 1;
	while (*p != NULL && **p == '-') {
		//二级指针可创建多个一级指针变量进行简化
		char* str = *p;
		char*  curr= str + 1;
		while (*curr != '\0') {
			int isin = 0;
			char* r = control;
			char ch = *curr;
			while (*r != '\0') {
				if (ch == *r) {
					isin = 1;
					break;
				}
				r++;
			}
			if (isin && *(r + 1) != '+') {
				do_arg(ch, NULL);
			}
			else if (isin && *(r + 1) == '+') {
				if ( *(curr+1)!= '\0') {
					do_arg(ch,curr+1);
					//不用遍历后续字符串
					while (*curr) curr++;
				}
	/*	地址计算不可能为空，
	    对指向空内容的地址间接引用才能判断是否为空
		指针变量可以被赋值为NULL，那是不是可以看作地址为NULL，
		因为指针变量的值恰好表示地址，
		但是如果为指针赋值为NULL又不可以使用间接引用，
		这是个无意义的指针，所以只作为一个判断条件*/

				else if (*(curr + 1) == '\0' && *(p + 1) == NULL) {
					illegal_arg(ch);
				}
				else if (*(curr + 1) == '\0' && *(p + 1) != NULL) {
					do_arg(ch, *(p + 1));
					p++;
				}

			}
			else {
				illegal_arg(ch);
			}
			curr++;
		}
		p++;
	}
	return p;
}
   /*whi1e 下一次参数以一个横杠开头*/
  /* 对于参数横杠后面的每个字符处理字符:
   首先观察字符是否位于control字符串内（3种情况）
   1.如果它并不位于那里，调用ilegal_arg所指向函数，
	   把这个字符作为参数传递过去。
   2.如果它位于control字符串内，但它的后面并不是跟一个 + 号，
	   那么就调用do_arg所指向的函数，
	   把这个字符和一个NULL指针作为参数传递过去。
   3.如果该字符位于control字符串内并且后面跟一个 + 号，
	   那么就应该有一个值与这个字符相联系。
	   a.如果当前参数还有其他字符，它们就是我们需要的值。
	   b.否则，下一个参数才是这个值。

   在任何一种情况下，你应该调用do_arg所指向的函数，
   把这个字符和指向这个值的指针传递过去。
   如果不存在这个值(当前参数没有其他字符，且后面不再有参数)，
   那么你应该改而调用ilegal_arg函数。
   注意:你必须保证这个值中的字符以后不会被处理。*/

 
   /*返回一个指针，指向下一个参数指针。
   * 当所有以一个横杠开头的参数被处理完毕后，
   你应该返回一个指向下一个命令行参数的指针的指针
   (也就是一个诸如&argv[4]或argv+4的值)。
   如果所有的命令行参数都以一个横杠开头，
   你就返回一个指向“命令行参数列表中结尾的NULL指针”的指针。
   */

	/*这个函数必须既不能修改命令行参数指针，也不能修改参数本身。*/
