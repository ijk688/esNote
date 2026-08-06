#include<stdio.h>
#include<stdlib.h>
//链式队列标准化结构定义

//链式队列节点结构定义
typedef struct lqNode {
	//数据域
	int data;
	//指针域
	struct lqNode* next;
}lqnode;
//链式队列结构定义
typedef struct LinkQueue {
	//队头指针，始终指向第一个数据节点
	//出队
	lqnode* front;
	//队尾指针，始终指向尾节点
	//入队
	lqnode* rear;
}linkqueue;


linkqueue* lqCreate();
int lqDestroy(linkqueue** lq);
int isEmpty(linkqueue* lq);
int getLength(linkqueue* lq);
int printfLq(linkqueue* lq);
int Enqueue(linkqueue* lq, int data);
int Dequeue(linkqueue* lq, int* outData);
int getFront(linkqueue* lq, int* outData);
int lqClear(linkqueue* lq);
 
int main() {
	//初始化链式队列
	linkqueue* lq = lqCreate();
	//入队
	int res = 0;
	res = Enqueue(lq, 1);
	res = Enqueue(lq, 2);
	res = Enqueue(lq, 3);
	res = Enqueue(lq, 4);
	int b = -1;
	int c = -1;
	res = Dequeue(lq, &b);
	res = getFront(lq, &c);
	printf("出队元素：%d\n", b);
	printf("队头元素：%d\n", c);
	lqClear(lq);
	//输出元素个数
	printf("链式队列元素个数为:%d\n", getLength(lq));
	//打印遍历
	printfLq(lq);
	//销毁
	if (lqDestroy(&lq) == 1) printf("销毁完成\n");
	return 0;
}


//不带头结点，节省内存
//初始化链式队列
linkqueue* lqCreate() {
	//创建队空
	linkqueue* lq = (linkqueue*)malloc(sizeof(linkqueue));
	if (lq == NULL) {
		printf("动态内存分配失败\n");
		return NULL;
	}
	//初始化队头，队尾
	lq->front = NULL;
	lq->rear = NULL;
	return lq;
}
//销毁
int lqDestroy(linkqueue** lq) {
	//处理传参问题
	if (lq == NULL || *lq == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//遍历可包含队空情况
	lqnode* p = (*lq)->front;
	lqnode* n = NULL;
	while (p != NULL) {
		//保存p指针
		n = p;
		//移动p指针
		p = p->next;
		//释放此前位置
		free(n);
	}
	//队中节点销毁完毕后，销毁队
	free(*lq);
	//悬空指针
	*lq = NULL;
	return 1;
}
//判空
int isEmpty(linkqueue* lq) {
	//处理传参问题
	if (lq == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//判断队首即可
	if (lq->front == NULL) return 1;
	return 0;
}
//获取元素个数
int getLength(linkqueue* lq) {
	//处理传参问题
	int r = isEmpty(lq);
	if (r == -1) return -1;
	//利用头节点遍历
	lqnode* p = lq->front;
	//计数
	int count = 0;
	while (p != NULL) {
		count++;
		p = p->next;
	}
	//返回元素个数
	return count;
}
//打印遍历
int printfLq(linkqueue* lq) {
	//处理传参问题
	int r = isEmpty(lq);
	if (r == -1) return -1;
	//保证p!=NULL
	if (r == 1) return -1;
	lqnode* p = lq->front;
	while (p->next != NULL) {
		printf("%d,", p->data);
		p = p->next;
	}
	printf("%d\n", p->data);
	//遍历结束
	return 1;
}
//入队
int Enqueue(linkqueue* lq, int data) {
	//处理传参问题
	int r = isEmpty(lq);
	if (r == -1) return -1;
	//初始化新节点
	lqnode* n = (lqnode*)malloc(sizeof(lqnode));
	if (n == NULL) {
		printf("动态内存分配失败\n");
		return -1;
	}
	n->data = data;
	n->next = NULL;
	//队空
	if (r == 1) {
		lq->front = n;
		lq->rear = n;
		return 1;
	}
	//基于尾插实现
	//即front控制出队，rear控制入队
	//单链表特性使用头插不方便出队
	//需要额外遍历
	//此前队尾节点指向新节点
	lq->rear->next = n;
	//队尾节点赋值为新节点
	lq->rear = n;
	return 1;
}
//出队
int Dequeue(linkqueue* lq, int* outData) {
	//处理传参问题
	int r = isEmpty(lq);
	if (r == -1 || outData == NULL) return -1;
	if (r == 1) return -1;
	//特殊情况只有一个队首节点
	//尾指针置空
	if (lq->front == lq->rear) lq->rear = NULL;
	//保存队头指针和值
	lqnode* n = lq->front;
	*outData = lq->front->data;
	//移动队头
	lq->front = lq->front->next;
	//释放原队头内存
	free(n);
	return 1;
}
//获取队头元素
int getFront(linkqueue* lq, int* outData) {
	//处理传参问题
	int r = isEmpty(lq);
	if (r == -1 || outData == NULL) return -1;
	if (r == 1) return -1;
	//保存队头值
	*outData = lq->front->data;
	return 1;
}
//清空
int lqClear(linkqueue* lq) {
	//处理传参问题
	int r = isEmpty(lq);
	if (r == -1) return -1;
	if (r == 1) return 1;
	//遍历释放各节点内存
	lqnode* p = lq->front;
	lqnode* n = NULL;
	while (p != NULL) {
		n = p;
		p = p->next;
		free(n);
	}
	//悬空队头队尾指针
	lq->front = NULL;
	lq->rear = NULL;
	return 1;
}