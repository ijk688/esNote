#include<stdio.h>
typedef struct allMoney{
	float sugprice;
	float sellprice;
	float saletax;
	float lifee;
}aM;
typedef struct zujie{
	float sugprice;
	float sellprice;
	float downpay;
	float secdeposit;
	float monpay;
	int leaseterm;
}zj;
typedef struct daikuan{
	char bankname[20];
	float sugprice;
	float sellprice;
	float saletax;
	float lifee;
	float dounpay;
	float intrate;
	float monpay;
    int loandura;
}dk;
typedef union type{
	aM a1;
	zj a2;
	dk a3;
}tp;
typedef struct document{
	char cusaddress[40];
	char cusname[20];
	char model[20];
	tp sedoc;
}doc;
int main(){
	doc d1;
	d1.sedoc.a1.lifee=11.2;
	doc *d2;
	(*d2).sedoc.a1.lifee=11.2;
	d2->sedoc.a1.lifee=11.2;
	return 0;
}

