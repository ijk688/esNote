#include<stdio.h>
#define MAX 10
//char *find_char(char const *source,char const *chars){
// 
//   const char* p=source;
//   const char* q=chars;
//    int isture=0;
//    for(int i=0;*(p+i)!='\0';i++){
//        for(int j=0;*(q+j)!='\0';j++){
//    		if(*(p+i)==*(q+j)){
//    			  isture=1;
//    			  printf("for over\n");
//    			  printf("%c\n",*(p+i));
//    		      return (char *)p+i;
//			}
//		}
//		
//	}
//	if(isture==0){
//		printf("if over\n");
//		return NULL;
//		
//	}
//}
//char *find_char(char const *source,char const *chars){
//	if(*source!='\0'){
//		const char* p=source;
//			while(*p!='\0'){
//		if(*chars!='\0'){
//			const char* q=chars;
//				while(*q!='\0'){
//			if(*p==*q){
//				return (char *)p;
//			}
//			else q++;
//		}
//		}
//			p++;
//	}
// 
//	}
//	return NULL;
// 
//	
//}
char *find_char(char const *source,char const *chars){
	if(*source!='\0'){
			const char* q=chars;
		while(*q!='\0'){
			if(*source==*q){
				return (char *)source;
			}
			else q++;
		}
		
			source++;
	}
	return NULL;
 
	
}
int main(){
//	printf("over\n");
//	printf("over\n");
//	char ch='a';
//	char* p=&ch;
//	printf("%c",*p);
    const char* source="abcd";
    const char* chars="ijk";
    char* res=find_char(source,chars);
	 
	if(res!=NULL){
		printf("%c",*res);
	}
	else{
		printf("return NULL");
	}
	return 0;
}
