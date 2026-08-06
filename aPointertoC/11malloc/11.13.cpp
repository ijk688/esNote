#include<stdio.h>
#include<stdlib.h>
#define MAX 50
char *instr();
int main() {
	char *o=instr();
	char* q = o;
	if (o!= NULL) {
		while (*q != '\0') {
			printf("%c\n", *q);
			q++;
		}
	}
	free(o);
 
	return 0;
}
char* instr() {
	char c;
	char* str=(char*)malloc(MAX*sizeof(char));
	if (str == NULL) {
		return NULL;
	}
	char* p = str;
	while (1) {
		scanf_s("%c", &c);
		if (c == '#') break;
		*p++ = c;
	}
	*p = '\0';
	return str;
}
