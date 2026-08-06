#include<stdio.h>
#include<stdlib.h>
typedef struct Stack {
	//栈中元素
	int* data;
	//栈顶下标
	//栈空 -1
	//栈满 maxSize-1
	//有效元素个数 top+1
	int top;
	//栈中能容纳的最大元素数量
	int maxSize;
}stack;

//初始化
stack* sCreate(int max);
//销毁
int stackDestroy(stack** s);
//判空
int isEmpty(stack* s);
//判满
int isFull(stack* s);
//获取元素个数
int getSize(stack* s);
//入栈，栈顶添加元素
int stackPush(stack* s, int data);
//自下往上打印栈
int printfStack(stack* s);
//出栈
int stackPop(stack* s, int* topValue);
//获取栈顶元素值
int stackGetTop(stack* s, int* topValue);
//清空栈
void stackClear(stack* s);
 










///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int main() {
	stack* s = sCreate(2);
	int res = 0;
	int b = 0;
	int c = 0;
	res = stackPush(s, 1);
	res = stackPush(s, 2);
	//res = stackPush(s, 3);
	//res = stackPush(s, 4);
	//res = stackPush(s, 5);
	res = stackPop(s, &b);
	res = stackGetTop(s, &c);
	printf("popOutData:%d\n", b);
	printf("topData:%d\n", c);
	stackClear(s);
	//输出元素个数
	printf("顺序栈共%d个有效元素\n", getSize(s));
	//自下而上打印遍历有效元素
	int a = printfStack(s);
	if (a == 0) printf("栈空\n");
	//销毁顺序栈
	if (stackDestroy(&s)==1) printf("顺序栈销毁成功\n");
	return 0;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////









//出栈，删除栈顶，带出栈顶值
int stackPop(stack* s, int* topValue) {
	//处理传参问题
	if (topValue == NULL) return -1;
	int r = isEmpty(s);
	if (r == -1) return -1;
	else if (r == 1) return -1;
	//存在有效元素
	//保存栈顶值
	//规范化：*(s->data + s->top)等价于s->data[s->top]
	*topValue = s->data[s->top];
	//移动栈顶下标
	s->top--;
	return 1;
}
//取栈顶，只读不删
int stackGetTop(stack* s, int* topValue) {
	//处理传参问题
	if (topValue == NULL) return -1;
	int r = isEmpty(s);
	if (r == -1) return -1;
	else if (r == 1) return -1;
	//存在有效元素
	//保存栈顶值
	*topValue = s->data[s->top];
	return 1;
}
//清空所有元素，不释放内存
void stackClear(stack* s) {
	//处理传参问题
	int r = isEmpty(s);
	if (r == -1) return;
	//栈顶下标复原
	s->top = -1;
}
//初始化
stack* sCreate(int max) {
	//处理传参问题
	if (max <= 0) {
		printf("给定值超出范围最小值\n");
		return NULL;
	}
	stack* s = (stack*)malloc(sizeof(stack));
	if (s == NULL) {
		printf("动态内存分配失败\n");
		return NULL;
	}
	s->top = -1;
	s->maxSize = max;
	s->data = (int*)malloc(sizeof(int) * s->maxSize);
	if (s->data == NULL) {
		printf("动态内存分配失败\n");
		//释放栈整体
		free(s);
		return NULL;
	}
	//成功创建容量为max的顺序栈
	return s;
}
//销毁
int stackDestroy(stack** s) {
	//处理传参问题
	if (s == NULL || *s == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//销毁元素数组
	free((*s)->data);
	//销毁顺序栈入口
	free(*s);
	//悬空指针
	*s = NULL;
	return 1;
}
//判空
int isEmpty(stack* s) {
	//处理传参问题
	if (s == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//根据栈顶下标判断栈空
	if (s->top == -1) return 1;
	//否则
	return 0;
}
//判满
int isFull(stack* s) {
	//处理传参问题
	if (s == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//根据栈顶下标判断栈满
	if (s->top == s->maxSize - 1) return 1;
	//否则
	return 0;
}
//得到元素个数
int getSize(stack* s) {
	//处理传参问题
	if (s == NULL) {
		printf("传参为空\n");
		return -1;
	}
	return s->top + 1;
}
//增
int stackPush(stack* s, int data) {
	int r = isEmpty(s);
	//处理传参错误
	if (r == -1) return -1;
	//处理栈满
	int e = isFull(s);
	if (e == 1) {
		//申请扩容，倍数扩容
		int newSize = 2 * s->maxSize;
		//采用临时指针
		int* tmp = (int*)realloc(s->data, sizeof(int) * newSize);
		if (tmp == NULL) {
			printf("动态内存分配失败\n");
			return -1;
		}
		//否则
		s->data = tmp;
		s->maxSize = newSize;
	}
	//栈空等其他情况正常加入
	s->top++;
	*(s->data + s->top) = data;
	return 1;
}
//自下而上遍历
int printfStack(stack* s) {
	//处理传参问题
	int r = isEmpty(s);
	//NULL
	if (r == -1) return -1;
	//栈空
	else if (r == 1) return 0;
	//循环有效元素-1次
	for (int i = 0;i < s->top;i++) {
		printf("%d,", *(s->data + i));
	}
	//最后打印栈顶元素
	printf("%d\n", *(s->data + s->top));
	return 1;
}