#include<stdio.h>
#include <stdbool.h>
bool identity_matrix(int num,int (*matrix)[10]){
	 for(int i=0;i<num;i++){
	 	for(int j=0;j<num;j++){
	 		if(i==j&&*(*(matrix+i)+j)!=1) return false;
	 		else if(i!=j&&*(*(matrix+i)+j)!=0) return false;
		 }
	 }
	 return true;
}
int main() {
    int matrix[10][10] = {
        {1,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,1}
    };
    printf("%d",identity_matrix(10,matrix));
	return 0;
}
