#include<stdio.h>
int main(){
	int line_num=1;
	int ch;
	printf("1.");
	while((ch=getchar())!=EOF){
		putchar(ch);
		
		if(ch=='\n'){
			line_num++;
			printf("%d.",line_num);
		}
	}
	return 0;
}
