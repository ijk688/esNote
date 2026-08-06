#include<stdio.h>
#define MAX 10
char* my_strcpy(char* a,const char* b,int strength);
int main(){
	char a[MAX]="0123";
	char b[MAX]="3673";
	printf("%s",my_strcpy(a,b,4));
	return 0;
}
char* my_strcpy(char* a,const char* b,int strength){
	char* c=a;
	int i=0;
	while(i<strength-1&&*b!='\0'){
		*a++=*b++;
		i++;
	} 
    *a='\0';
    return c;
}
//	char* d=b;
//	int countb=0; 
//	while(*b!='\0'){
//		countb++;
//		b++;
//	}
//    if(strength>=countb){
//    	while(*d!='\0'){
//    		*a++=*d++;
//		}
//	}
//	else{
//		while(strength--){
//			*a++=*d++;
//		}
//	}
