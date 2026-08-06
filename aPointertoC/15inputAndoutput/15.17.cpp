#include<stdio.h>
#include<string.h>
#define MAX 256
//函数应该接收所有一个表示整数的字符
//并输出对应的整形数用于后续计算
int conchar(char* p) {
	int a = 0;
	int b = 0;
	char* q = p;
	while (*q != '\0') {
		b = *q - '0';
		q++;
		a = a * 10 + b;
	}
	return a;
}
float avg(int a, int b) {
	float c = (float)a;
	float d = (float)b;
	return c / d;
}
int main7() {
	
	FILE* file = NULL;
	errno_t err = fopen_s(&file, "avgAge.txt", "r");
	//fopen_s函数成功返回0
	if (err == 0) {
		char string[MAX];
		while (fgets(string, MAX, file) != NULL) {
			int sum = 0;
			char* p = string;
			char q[MAX] = { 0 };
			int j = 0;
			int count=0;
			//printf("%s\n", string);
			//计算字符串长度，遍历每个字符，取出表示数字的字符
			//可以写一个函数，对数字字符进行处理
			//最后计算平均值得到结果
			size_t num = strlen(string);
			for (int i = 0;i < num;i++) {
				char ch = string[i];
				if (ch >= '0' && ch <= '9') {
					q[j++] = ch;
				}
				//判断字符串是否为空，依次来转换
				//依据选择变化情况小的，最好是唯一的
				//所以字符串为空即为最好情况
				else {
					if (j > 0) {
						q[j] = '\0';
						sum += conchar(q);
						count++;
						j = 0;
						memset(q, 0, sizeof(q));
					}
				}
			}
		 
			if (j > 0) {
				q[j] = '\0';
				sum += conchar(q);
				count++;
			}
			//
		/*		for (int i = 0;i < num;i++) {
					
					if (*(p + i) >= '0' && *(p + i) <= '9') {
						*(q + j) = *(p + i);
						j++;
					}
					else {
						if (*(p + i) == ' ') {
							count++;
						}
						*(q + j) = '\0';
						j = 0;
					   sum+=conchar(q);

					}

				}*/
		/*	if (strchr(string, '\n') == NULL) {
					*(q + j) = '\0';
					j = 0;
					sum += conchar(q);
			}*/
			printf("%5.2f\n%s\n", avg(sum,count),p);
		}
	}
	if (file != NULL) {
		fclose(file);
	}
	return 0;
}