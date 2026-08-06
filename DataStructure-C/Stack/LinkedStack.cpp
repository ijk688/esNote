#include<stdio.h>
#include<stdlib.h>
//标准链式栈结构定义

//链式栈节点结构定义
typedef struct StackNode {
	//数据域
	int data;
	//指针域
	struct StackNode* next;
}snode;
//链式栈本体（栈头）结构定义
//不封装会增加使用二级指针的情况
typedef struct LinkStack{
	//栈顶指针
	snode* top;
}lstack;


lstack* lsCreate();
int lsDestroy(lstack** lshead);
int isEmpty(lstack* lshead);
int getLength(lstack* lshead);
int printfls(lstack* lshead);
int lsPush(lstack* lshead, int data);
int lsPop(lstack* lshead, int* outData);
int getlsTop(lstack* lshead, int* outData);
int lsClear(lstack* lshead);

int main() {
	//创建栈头
	lstack* lshead = lsCreate();
	int r = -1;
	//入栈
	r = lsPush(lshead, 2);
	r = lsPush(lshead, 3);
	r = lsPush(lshead, 4);
	int b = -1;
	int c = -1;
	r = lsPop(lshead, &b);
	printf("出栈元素：%d\n", b);
	r = getlsTop(lshead, &c);
	printf("栈顶元素：%d\n", c);
	//输出元素个数
	printf("当前链式栈的元素个数为:%d\n", getLength(lshead));
	//打印遍历
	printfls(lshead);
	//销毁
	if (lsDestroy(&lshead) == 1) {
		printf("销毁完成\n");
	}
	return 0;
}

//初始化链式栈
//采用不带头结点
lstack* lsCreate() {
	//栈头进行动态内存分配
	lstack* lshead = (lstack*)malloc(sizeof(lstack));
	if (lshead == NULL) {
		printf("动态内存分配失败\n");
		return NULL;
	}
	//栈顶指针进行动态内存分配
	lshead->top = (snode*)malloc(sizeof(snode));
	if (lshead->top == NULL) {
		printf("动态内存分配失败\n");
		//释放栈头
		free(lshead);
		return NULL;
	}
	//初始化栈顶指针
	lshead->top = NULL;
	//返回栈头
	return lshead;
}
//销毁
int lsDestroy(lstack** lshead) {
	//处理传参问题
	if (lshead == NULL || *lshead == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//遍历整栈，依次释放内存
	snode* p = (*lshead)->top;
	snode* n = NULL;
	//释放栈中元素内存
	while (p != NULL) {
		//记录指针
		n = p;
		//移位
		p = p->next;
		//释放
		free(n);
	}
	//释放栈内存
	free(*lshead);
	//悬空栈指针
	*lshead = NULL;
	return 1;
}
//判空
int isEmpty(lstack* lshead) {
	if (lshead == NULL) {
		printf("传参为空\n");
		return -1;
	}
	if (lshead->top == NULL) return 1;
	//否则不为空
	return 0;
}
//获取元素个数
int getLength(lstack* lshead) {
	//返回元素个数
	//处理传参问题
	int r = isEmpty(lshead);
	if (r == -1) return -1;
	else if (r == 1) return 0;
	//栈顶遍历到栈底
	snode* p = lshead->top;
	//计数
	int count = 0;
	while (p != NULL) {
		//后置移位
		count++;
		p = p->next;
	}
	return count;
}
//打印遍历
int printfls(lstack* lshead) {
	//处理传参问题
	int r = isEmpty(lshead);
	if (r == -1) return -1;
	else if (r == 1) return -1;
	//栈顶遍历到栈底
	snode* p = lshead->top;
	while (p->next != NULL) {
		//后置移位
		printf("%d,", p->data);
		p = p->next;
	}
	//p指向栈底
	printf("%d\n", p->data);
	//打印完成
	return 1;
}
//入栈
int lsPush(lstack* lshead, int data) {
	//处理传参问题
	int r = isEmpty(lshead);
	if (r == -1) return -1;
	//创建新节点
	snode* n = (snode*)malloc(sizeof(snode));
	if (n == NULL) {
		printf("动态内存分配失败\n");
		return -1;
	}
	n->data = data;
	//新节点指向栈顶指针
	n->next = lshead->top;
	//栈顶指针变为新节点
	lshead->top = n;
	//入栈完成
	return 1;
}
//出栈
int lsPop(lstack* lshead, int* outData) {
	//处理传参问题
	int r = isEmpty(lshead);
	if (r == -1 || outData == NULL) return -1;
	//栈空
	if (r == 1) return -1;
	//保存栈顶节点值
	*outData = lshead->top->data;
	//含有其他节点，保存栈顶节点位置
	snode* n = lshead->top;
	//移动栈顶节点
	lshead->top = lshead->top->next;
	//释放栈顶节点内存
	free(n);
	//出栈完成
	return 1;
}
//取栈顶元素
int getlsTop(lstack* lshead, int* outData) {
	//处理传参问题
	int r = isEmpty(lshead);
	if (r == -1 || outData == NULL) return -1;
	//栈空
	if (r == 1) return 1;
	//保存栈顶节点值
	*outData = lshead->top->data;
	return 1;
}
//清空所有元素
int lsClear(lstack* lshead) {
	//处理传参问题
	int r = isEmpty(lshead);
	if (r == -1) return -1;
	//栈空
	if (r == 1) return -1;
	//销毁所有节点，栈顶节点置空
		//遍历整栈，依次释放内存
	snode* p = lshead->top;
	snode* n = NULL;
	//释放栈中元素内存
	while (p != NULL) {
		//记录指针
		n = p;
		//移位
		p = p->next;
		//释放
		free(n);
	}
	//栈顶指针置空
	lshead->top = NULL;
	return 1;
}