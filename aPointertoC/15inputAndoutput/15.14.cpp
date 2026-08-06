#include<stdio.h>
#include<string.h>
#define MAX 10

int main4() {
	char inName[MAX];
	char outName[MAX];
	printf("请输入原文件名：\n");
	fgets(inName, MAX, stdin);
	inName[strcspn(inName, "\n")] = '\0';
	printf("请输入目标文件名：\n");
	fgets(outName, MAX, stdin);
	outName[strcspn(outName, "\n")] = '\0';
 
	FILE* file=NULL;
	FILE* file1=NULL;
	errno_t err= fopen_s(&file,inName, "r");
	errno_t err1 = fopen_s(&file1, outName, "w");
	if (!err&&!err1) {		
		char str[MAX];
		while (fgets(str, MAX, file) != NULL) {
			fputs(str,file1);
			while (strchr(str, '\n') == NULL) {

				if (fgets(str, MAX, file) == NULL) break;
					fputs(str, file1);
			}
		}
	}
	if(file!=NULL) fclose(file);
	if(file1!=NULL) fclose(file1);
	return 0;
}