#include<stdio.h> 
#define MAX 10

int del_substr(char *str,char const *substr){
	char *o=str;
	char newstr[MAX]={'\0'};
	char *f=newstr;
	while(*str!='\0'){	
        char const *p=substr;
        char *num=str;
		while(*str==*p&&*p!='\0'){
				str++;
				p++;
		}
		if(*p=='\0') {
		    char *q=str;
			while(o<num){
				*f=*o;
				f++;
				o++;
			}
		    while(*q!='\0'){
		          *f=*q;
		          f++;
		          q++;
		    	
			}
			*f++='\0';
		  printf("%s\n",newstr);
		return 1;	
		} 
		str=num;
		str++;
	}
	return 0;
}
int main(){
	char str[MAX]={'A','B','D','e','B','E'};
	char const substr[MAX]={'B','D'};
	printf("%d\n",del_substr(str,substr)) ;	
	return 0;
}
