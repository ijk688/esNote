#include<stdio.h>
typedef struct misc{
	unsigned int opcode :4;
}misc;
typedef struct branch{
	unsigned int offset:8;
	unsigned int opcode:8;
}branch;
typedef struct sgl_op{
	unsigned int dst_reg :3;
	unsigned int dst_mode:3;
	unsigned int src_reg:3;
	unsigned int src_mode:3;
	unsigned int opcode:4;
}sgl_op;
typedef struct reg_src{
	unsigned int dst_reg:3;
	unsigned int dst_mode:3;
	unsigned int src_reg:3;
	unsigned int opcode:7;
}reg_src;
typedef struct dbl_op{
	unsigned int dst_reg:3;
	unsigned int dst_mode:3;
	unsigned int opcode:10;
}dbl_op;
typedef union type{
 misc m;
 branch b;
 sgl_op s;
 reg_src r;
 dbl_op d;	
}tp;
typedef struct mi{
	unsigned short addr;
    tp t;
}machine_inst;
int main(){
	machine_inst x;
	x.t.r.src_reg = 0x7;
	printf("%d",x.t.r.src_reg);
	return 0;
}
