#include<stdio.h> 
#define MAX 5
int my_strlen(const char* string,int strength);
int main(){
	char string[MAX]={'1','2','3','\0','\0'};
	printf("%d\n",my_strlen(string,5)) ;
	return 0;
}
int my_strlen(const char* string,int strength){
	int count=0;
	for(int i=0;i<strength;i++){
		if(*string=='\0'){ 
//		  return count;
         break;
		} 
		else  {
			count++;
			string++;
		} 	
	}
	return count;
}
