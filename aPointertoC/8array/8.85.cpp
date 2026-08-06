#include<stdio.h>
void matrix_multiply(int* m1,int* m2,int* r,int x,int y,int z);
int main(){
	int m1[3][2]={2,-6,3,5,1,-1};
	int m2[2][4]={4,-2,-4,-5,-7,-3,6,7};
	int r[3][4]={0};
	matrix_multiply((int *)m1,(int *)m2,(int *)r,3,2,4);
	return 0;
}
void matrix_multiply(int* m1,int* m2,int* r,int x,int y,int z){
	int sumr=x*z;
	int sum1=x*y;
	int sum2=y*z;
	for(int i=0;i<x;i++){
		for(int j=0;j<z;j++){
			for(int k=0;k<y;k++){
				(*((r+i*z)+j))+=(*((m1+i*y)+k))*(*((m2+k*z)+j));
//				r[i][j]+=m1[i][k]*m2[k][j];
			}
		}
	}
    for(int i=0;i<sumr;i++){
     printf("%d,\n",*r) ;
     r++;
	}
}

