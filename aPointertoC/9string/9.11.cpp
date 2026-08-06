#include<stdio.h> 
#include<ctype.h>
#define MAX 10000 
int main(){
	char string[MAX];
	int count[6]={0};
	char a;
	int b1=0;
	while(1){
		scanf("%c",&a);
		if(a=='#') break;
		string[b1]=a;
		b1++;
	}
	float b=b1;
	for(int i=0;i<b1;i++){
		if(iscntrl(string[i])) count[0]++;
		else if(isspace(string[i])) count[1]++;
		else if(isdigit(string[i])) count[2]++;
		else if(islower(string[i])) count[3]++;
		else if(isupper(string[i])) count[4]++;
		else if(ispunct(string[i])) count[5]++;
	}
 
	printf("%d\n",sum) ;
	printf("一共输入%d个字符\n",b1); 
	printf("控制字符占比：%f\n",count[0]/b); 
	printf("空白字符占比：%f\n",count[1]/b); 
	printf("数字字符占比：%f\n",count[2]/b); 
	printf("小写字母字符占比：%f\n",count[3]/b); 
	printf("大写字母字符占比：%f\n",count[4]/b); 
	printf("标点符号字符占比：%f\n",count[5]/b); 
 
	return 0;
}
//函数	功能说明（判断字符是否为...）	适用字符范围
//isalpha(c)	字母（a-z、A-Z）	大小写英文字母
//isdigit(c)	十进制数字（0-9）	0 1 2 ... 9
//isalnum(c)	字母或数字（字母 + 数字）	字母 + 0-9
//islower(c)	小写字母（a-z）	a b c ... z
//isupper(c)	大写字母（A-Z）	A B C ... Z
//isspace(c)	空白字符	空格、制表符\t、换行\n等
//ispunct(c)	标点符号（非字母、数字、空白的可打印字符）	! @ # , . ; 等符号
//isprint(c)	可打印字符（能显示在屏幕上）	字母、数字、标点、空格
//iscntrl(c)	控制字符（不可打印）	\n \t \b 等转义字符
//isxdigit(c)	十六进制数字	0-9、a-f、A-F
