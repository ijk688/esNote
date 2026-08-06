#include<stdio.h> 
#define MAX 20
typedef struct phoneNum{
	char quhao[MAX];
	char jiaohan[MAX];
	char zhanhao[MAX];
	
}phoneNum;
typedef struct farCall{
	phoneNum unum;
	phoneNum cnum;
	phoneNum pnum; 
	char date[MAX];
	char time[MAX];
	 
}farCall;
int main(){
	return 0;
}
