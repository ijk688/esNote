#include<stdio.h> 
//暂以三维数组为例 
int array_offset(int arrayinfo[],int x,int y,int z);
int main(){
	int n=0;
	int x;
	int y;
	int z;
	int arrayinfo[1000]={0};
	printf("请输入arrayinfo中的值：\n");
	while(scanf("%d",&arrayinfo[n])!=EOF){
	     n++;
	}
//    for(int i=0;i<n;i++){
//    	printf("%d,",arrayinfo[i]);
//	}
 
//	printf("%d\n",array_offset(arrayinfo,x,y,z));
	return 0;
}
int array_offset(int arrayinfo[],int s1,int s2,int s3){
	int lo1=*(arrayinfo+1);
	int hi1=*(arrayinfo+2);
	int lo2=*(arrayinfo+3);
	int hi2=*(arrayinfo+4);
	int lo3=*(arrayinfo+5);
	int hi3=*(arrayinfo+6);
	
	int loc=((s1-lo1)*(hi2-lo2+1)+s2-lo2)*(hi3-lo3+1)+s3-lo3;
	
	return loc;
	
}
