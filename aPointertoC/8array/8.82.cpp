#include<stdio.h> 
float single_tax(float income){
	if(0<income<=23350) return 0.15*income;
	else if(23350<income<=56550) return 3502.50+0.28*(income-23350);
	else if(56550<income<=117950) return 12798.50+0.31*(income-56550);
	else if(117950<income<=256500) return 31832.50+0.36*(income-117950);
	else if(income>256500) return 81710.50+0.396*(income-256500);
}
int main(){
	int income;
    printf("请输入你的税前收入；\n");
    scanf("%d",&income);
    printf("你的所需缴税为：%f",single_tax(income));
	return 0;
}
