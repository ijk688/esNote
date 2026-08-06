#include<stdio.h> 
#define MAX 10 
//void my_strcat(char* dest,const char* src,int max);
char* my_strcat(char* dest,const char* src,int max);

int main(){
	char s[MAX]="Hello,";
	char d[MAX]="World";
	printf("%s\n",my_strcat(d,s,MAX));
	return 0;
}
char* my_strcat(char* dest,const char* src,int max){
	int a=0;
	int b=0;
	const char* s=src; 
	char* d=dest;
	while(*d!='\0'){
		a++;
		d++;
	}
	while(*src!='\0'){
		b++;
		src++;
	}
	if(a+b>max-1){
		printf("÷¥––if”Ôæ‰\n"); 
	    int yu=max-a-1;
		while(yu--){ 
			*d++=*s++;
		} 
	}
	else{
	printf("÷¥––else”Ôæ‰\n") ;
		while(*s!='\0'){
			 *d++=*s++;
		} 
	}
	*d='\0';
	return dest;
}
//void strcat(char* dest,const char* src,int max){
//	int a=0;
//	int b=0;
//	const char* s=src; 
//	char* d=dest;
//	while(*dest!='\0'){
//		a++;
//		dest++;
//	}
//	while(*src!='\0'){
//		b++;
//		src++;
//	}
//	if(a+b>max-1){
//		printf("÷¥––if”Ôæ‰\n"); 
//	    int yu=max-b;
//		while(yu--){
//			*dest++=*s++;
//		} 
//		*(dest+max-1)='\0';
//	}
//	else{
//	printf("÷¥––else”Ôæ‰\n") ;
//		while(*s!='\0'){
//			 *dest++=*s++;
//		} 
//	}
//	printf("%s\n",d);
//}
