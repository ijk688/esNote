#include<stdio.h> 
int hermite(int n,int x);
int main(){
	int a,b;
	printf("请输入n,x的值：\n");
	scanf("%d %d",&a,&b) ;
	printf("值为%d",hermite(a,b));
	return 0;
}
int hermite(int n,int x){
	if(n<=0) return 1;
	else if(n>=2) return 2*x*hermite(n-1,x)-2*(n-1)*hermite(n-2,x);
	else{
		return 2*x;
	}
}
 
