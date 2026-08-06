#include<stdio.h> 
#define MAX 50000
//2 3 5 7 11 13...
void Eratosthenes(int left,int right){
	if(left<2&&right<=MAX) printf("输入不合规");
	else{
	int num=0;
	int number=0;
	char numStorage[MAX]={0};
	int max=right;
	char *p=numStorage;
	while(max--){
		*p++='1';
	}
//	printf("%s\n",numStorage);
	char *q=numStorage;
    for(int i=2;i*i<=right;i++){
    	if(*(q+i)=='1'){
    		for(int j=i*i;j<=right;j+=i){
    			*(q+j)='0';
			}
		}
	}
	while(*q!='\0'){
		if(*q=='1'&&num>=left){
//			printf("%d\n",num);
			number++;
		}
		num++;
		q++;
	}
//	printf("%s\n",numStorage);
	printf("%d\n",number);
 
	}
}

int main(){
	for(int i=1000;i<=30000;i+=1000){
		Eratosthenes(i,i+1000);
	}
	return 0;
}
