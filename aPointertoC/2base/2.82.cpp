#include<stdio.h>
int main(){
	int ch;
	int left=0;
	int isfalse=0;
	while((ch=getchar())!=EOF){
		if(ch=='{'){
			left++;
		}
		else if(ch=='}'){
			left--;
			if(left<0) {
				isfalse=1;
				break;
			}
		}
	}
	if(isfalse==1&&left!=0) printf("1");
	else printf("0");
}
