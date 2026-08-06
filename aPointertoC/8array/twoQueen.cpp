#include<stdio.h>
#include<math.h>
int count=0;
void twoQueen(){
	for(int x1=0;x1<8;x1++){
			for(int y1=0;y1<8;y1++){
			for(int x2=0;x2<8;x2++){
			for(int y2=0;y2<8;y2++){
		    	if(x1!=x2&&y1!=y2&&abs(x2-x1)!=abs(y2-y1)) count++;
	}
	}
	}
	}
	printf("%d",count);
}
int main(){
	twoQueen();
	return 0;
}
