#include<stdio.h>
#if OPTION_LONG
void print_ledger_long(int num) {
	printf("long");
}
void print_ledger(int num) {
	print_ledger_long(num);
}
#elif OPTION_DETAILED
void print_ledger_detailed(int num) {
	printf("detailed");
}
void print_ledger(int num) {
	print_ledger_detailed(num);
}
#else
void print_ledger_default(int num) {
	printf("default");
}
void print_ledger(int num) {
	print_ledger_default(num);
}
#endif
int main1() {
	int num = 1;
	print_ledger(1);
	return 0;
}
