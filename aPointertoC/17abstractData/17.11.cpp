#include"stack.h"
#include<stdio.h>
#include<assert.h>
#include<malloc.h>

static STACK_TYPE* stack;
static size_t stack_size;
static int top_element = -1;

//发布版本定义 #define NDEBUG 后，assert 会被完全删除，代码消失。
void create_stack(size_t size) {
	assert(stack_size == 0);
	stack_size = size;
	stack = (STACK_TYPE*)malloc(stack_size * sizeof(STACK_TYPE));
	assert(stack != NULL);
}

void destroy_stack(void) {
	assert(stack_size > 0);
	stack_size = 0;
	free(stack);
}

void push(STACK_TYPE value) {
	assert(!is_full());
	top_element += 1;
	stack[top_element] = value;
}

void pop(void) {
	assert(!is_empty());
	top_element -= 1;
}

void resize_stack(size_t newsize) {
	STACK_TYPE* tmp = (STACK_TYPE*)realloc(stack,newsize * sizeof(STACK_TYPE));
	assert(tmp != NULL);
	stack = tmp;
	stack_size = newsize;
}
/*
**      top
*/
STACK_TYPE top(void)
{
	assert(!is_empty());
	return stack[top_element];
}

/*
**      is_empty
*/
int
is_empty(void)
{
	assert(stack_size > 0);
	return top_element == -1;
}

/*
**      is_full
*/
int
is_full(void)
{
	assert(stack_size > 0);
	return top_element == stack_size - 1;
}