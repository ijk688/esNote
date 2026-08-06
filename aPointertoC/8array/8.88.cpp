#include <stdio.h>
#include <math.h>
//回溯算法思想：走不通就回头，换条路再试，穷举所有可能，找到解就停。
int eightxy[8][2]={0};
int istrue(int x1,int y1,int x2,int y2){
	//不互吃 
	if(x1!=x2&&y1!=y2&&abs(x2-x1)!=abs(y2-y1)) return 1;
	//互吃
	else return 0； 
}

void eightQueen(){
	for(int i=0;i<8;i++){
		
	}
}

int main() {
    return 0;
}
