#include<stdio.h>
#define MAX 100
int max_list(int *array);
int main(){
	int array[MAX];
	int a;
	int b=0;
	printf("请输入一串整数：\n");
    while(1){
    	scanf("%d",&a);
    	if(a<0) break;
    	array[b++]=a;
	}
    printf("%d",max_list((int *)array)) ;
	return 0;
}
int max_list(int *array){
	int max=array[0];
    while(*array>=0){
    	if(*array>max) max=*array;
    	array++;
	}
    return max;
}
