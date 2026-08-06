#include<stdio.h>
int gcd(int m,int n);
int main(){
	int m,n;
	printf("请输入两个整数m,n:\n");
	scanf("%d %d",&m,&n);
	printf("最大公约数为：%d",gcd(m,n));
	return 0;
}
//int gcd(int m,int n){
//	if(m<=0||n<=0) return 0;
//	else{
//		if(m%n){
//			int r=m%n;
//			return gcd(n,r);
//		}
//		else return n;
//	}
//}
int gcd(int m,int n){
	if(m<=0||n<=0) return 0;
	return m%n?gcd(n,m%n):n;
}
