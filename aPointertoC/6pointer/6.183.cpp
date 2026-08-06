#include<stdio.h> 
#define MAX 100

void reverse_string(char *string);
int main(){
	char string[MAX]={'a','b','c','d'};
	reverse_string(string);
	printf("%s\n",string);
	return 0;
}

void reverse_string(char *string){
	char *p=string;
	char* q=string;
	while(*p!='\0'){
		p++;
	}
	p--;
    while(string<p){
		char temp; 
//	    printf("%c\n",*p);
//		printf("%c\n",*string);
	    temp=*p;
	    *p=*string;
	    *string=temp;
//	    printf("%c\n",*p);
//		printf("%c\n",*string);	
//		*p=*string;!!!!!!!´íÎó 
		string++;
		p--;
	}
	printf("%s\n",q);

 
}
