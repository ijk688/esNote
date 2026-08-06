#include<stdio.h>
#define VAX 1
#define CPU_VAX 1
#define CPU_68000 2
int cpu_type() {
#if defined(VAX)	
	return CPU_VAX;
#elif defined(M68000)
	return CPU_68000;
#endif
}
int main() {
	if (cpu_type() == 1) printf("vax");
	else if (cpu_type() == 2) printf("m68000");
	return 0;
}