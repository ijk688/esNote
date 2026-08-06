//#include<stdio.h>
//char** do_args(int argc, char** argv, char* control, 
//	           void (*do_arg)(int ch, char* value), 
//	           void (*illegal_arg)(int ch));
//void do_arg(int ch, char* value);
//void illegal_arg(int ch);
//int main5(int argc, char** argv) {
//
//	return 0;
//}
//
//void do_arg(int ch, char* value) {
//	printf("回调do_arg\n");
//	printf("%d\n", ch);
//}
//
//void illegal_arg(int ch) {
//	printf("回调illegal_arg\n");
//	printf("%d\n", ch);
//}
//
//char** do_args(int argc, char** argv, char* control,
//	void (*do_arg)(int ch, char* value),
//	void (*illegal_arg)(int ch)) {
//	/*跳过程序名参数*/
//	if (*(argv + 1) == NULL) {
//		return NULL;
//	}
//	char** p = argv+1;
//
//	/*whi1e 下一次参数以一个横杠开头*/
//	while (**p == '-') {
//		p++;
//		while (**p != '\0') {
//			char* q = control;
//			while (*q != '\0') {
//				if (**p == *q && *(q + 1) != '+') {
//					do_arg((int)*q, NULL);
//					/*2.如果它位于control字符串内，但它的后面并不是跟一个 + 号，
//					那么就调用do_arg所指向的函数，
//					把这个字符和一个NULL指针作为参数传递过去。*/
//				}
//				else if (**p == *q && *(q + 1) == '+') {
//					if (**++p == '\0'&&++p!=NULL) {
//						do_arg((int)*q, *(p+1));
//					}
//					else if (**++p == '\0' && ++p == NULL) {
//						illegal_arg((int)*q);
//					}
//					else {
//						do_arg((int)*q,*p);
//					}
//					/*3.如果该字符位于control字符串内并且后面跟一个 + 号，
//					那么就应该有一个值与这个字符相联系。
//					a.如果当前参数还有其他字符，它们就是我们需要的值。
//					b.否则，下一个参数才是这个值。*/
//				}
//				else {
//					/*1.如果它并不位于那里，调用ilegal_arg所指向函数，
//					把这个字符作为参数传递过去。*/
//					illegal_arg((int)*q);
//
//				}
//			}
//		}
//		p++;
//	}
//	if (p != NULL) {
//		return p;
//	}
//	else return NULL;
//	/*返回一个指针，指向下一个参数指针。
//	* 当所有以一个横杠开头的参数被处理完毕后，
//	你应该返回一个指向下一个命令行参数的指针的指针
//	(也就是一个诸如&argv[4]或argv+4的值)。
//	如果所有的命令行参数都以一个横杠开头，
//	你就返回一个指向“命令行参数列表中结尾的NULL指针”的指针。
//	*/
//	/*这个函数必须既不能修改命令行参数指针，也不能修改参数本身。*/
//}
/*在任何一种情况下，你应该调用do_arg所指向的函数，
把这个字符和指向这个值的指针传递过去。
如果不存在这个值(当前参数没有其他字符，且后面不再有参数)，
那么你应该改而调用ilegal_arg函数。
注意:你必须保证这个值中的字符以后不会被处理。*/