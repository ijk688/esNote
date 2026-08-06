#include<stdio.h>
#define MAX 100
int ascii_to_integer(char *string);
int main(){
	char string[MAX];
	printf("ÇëÊäÈëÒ»´®×Ö·û£º\n");
    scanf("%s",string);
    printf("%d",ascii_to_integer(string)) ;
	return 0;
}
int ascii_to_integer(const char *p){
	int res=0;
	while(*p!='\0'){
        if(*p<'0'||*p>'9') return 0; 
		res=res*10+(*p-'0');
		p++;
	}
	return res;
}
