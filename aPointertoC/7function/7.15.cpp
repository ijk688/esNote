#include<stdio.h>
#define MAX 100
void printD(const char *string,int a);
void printC(const char *string,char c);
void printInt(int a);
void printChar(char a);
int main(){
	int a=49;   
	float b=12.90;
	char c='a';
	printC("%c,",a);
	return 0;
}
void printC(const char* string,char c){
	while(*string!='\0'){
		if(*string=='%'&&*(++string)=='c'){
	        putchar(c);
			string++;
		}
		else{
		putchar(*string);
		string++;
		}
	}
} 
void printInt(int a){
	 if(a){
	    printInt(a/10);
	 	int b=a%10+'0';
	 	putchar(b);
	 }
	 
}
void printChar(int a){
	putchar(a);
}
void simPrintf(const char *string,int a){
	while(*string!='\0'){
		if(*string=='%'&&*(++string)=='d'){
	        printInt(a);
			string++;
		}
		else{
		putchar(*string);
		string++;
		}
	}
}
