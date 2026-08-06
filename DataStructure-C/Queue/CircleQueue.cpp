#include<stdio.h>
#include<stdlib.h>
typedef struct Queue {
	//存储有效元素
	int* data;
	//队首下标
	//出队：front=(front+1)%maxSize
	int front;
	//队尾下标
	//入队：rear=(rear+1)%maxSize
	int rear;
	//队空条件：front==rear
	//队满条件：（rear+1)%maxSize==front
	//有效最大存储个数：maxSize-1
	//最大容量
	int maxSize;
	//元素个数
	//(rear-front+maxSize)%maxSize.
}queue;

queue* qCreate(int max);
int queueDestroy(queue** q);
int isEmpty(queue* q);
int isFull(queue* q);
int getNum(queue* q);
int Enqueue(queue* q, int data);
int printfQueue(queue* q);
int Dequeue(queue* q, int* outData);
int getFront(queue* q, int* outData);
int queueClear(queue* q);



int main() {
	//创建队列
	queue* q = qCreate(2);
    //入队
	int res = 0;
	res=Enqueue(q, 1);
	res=Enqueue(q, 2);
	res=Enqueue(q, 3);
	//res=Enqueue(q, 4);
	int b = 0;
	int c = 0;
	res = Dequeue(q, &b);
	res = Dequeue(q, &b);
	res = Enqueue(q,4);
	res = Enqueue(q, 5);
	res = Enqueue(q, 5);
	//res = Dequeue(q, &b);
	//res = getFront(q, &c);
	//int d = queueClear(q);
	//输出出队元素值
	printf("出队元素值:%d\n", b);
	//输出队首元素值
	printf("队首元素值:%d\n", c);
	//输出当前最大容量
	printf("当前最大容量:%d\n", q->maxSize);
	//输出元素个数
	printf("当前元素个数为:%d\n", getNum(q));
	//打印队列
	if (printfQueue(q) == 1) {
		printf("打印完成\n");
	}
	//销毁队列
	if (queueDestroy(&q) == 1) {
		printf("内存释放成功\n");
	}
	
	return 0;
}




//初始化
queue* qCreate(int max) {
	//处理传参问题
	if (max <= 0) {
		printf("给定参数超出范围最小值\n");
		return NULL;
	}
	//开辟队列内存空间
	queue* q = (queue*)malloc(sizeof(queue));
	if (q == NULL) {
		printf("动态内存分配失败\n");
		return NULL;
	}
	//开辟元素内存空间
	q->data = (int*)malloc(sizeof(int) * max);
	if (q->data == NULL) {
		printf("动态内存分配失败\n");
		//释放队内存
		free(q);
		return NULL;
	}
	//初始化结构体成员
	q->front = 0;
	q->rear = 0;
	q->maxSize = max;
	return q;
}
//销毁
int queueDestroy(queue** q) {
	//处理传参问题
	if (q == NULL || *q == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//释放元素内存空间
	free((*q)->data);
	//释放队列内存空间
	free(*q);
	//悬空队列指针
	*q = NULL;
	return 1;
}
//判空
int isEmpty(queue* q) {
	//处理传参问题
	if (q == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//为真
	if (q->front == q->rear) return 1;
	return 0;
}
//判满
int isFull(queue* q) {
	//处理传参问题
	if (q == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//为真
	if ((q->rear + 1) % q->maxSize == q->front) return 1;
	return 0;
}
//获取元素个数
int getNum(queue* q) {
	//处理传参问题
	if (q == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//返回元素数量
	return (q->rear - q->front + q->maxSize) % q->maxSize;
}
//入队
int Enqueue(queue* q, int data) {
	//处理传参问题
	if (q == NULL) {
		printf("传参为空\n");
		return -1;
	}
	int r = isFull(q);
	//队满,倍数扩容
	if (r == 1) {
		int newSize = 2 * q->maxSize;
		//临时指针
		//不适用realloc
		//方式q->data变成野指针，不方便后续使用
		int* tmp = (int*)malloc(sizeof(int) * newSize);
		if (tmp == NULL) {
			printf("动态内存分配失败\n");
			return -1;
		}
		//扩容成功
		//q->data = tmp;
		//原队列元素需要顺序复制到新队列中
		//否则会导致计数错误
		//初始化新队列数组，用临时指针代替
		//遍历原队列
		int i = 0;
		for (int p = q->front;p != q->rear;p = (p + 1) % q->maxSize) {
			//依次赋值到新队列
			tmp[i] = q->data[p];
			i++;
		}
		//释放旧内存空间
		free(q->data);
		//新队列赋值给旧队列
		q->data = tmp;
		q->maxSize = newSize;
		//队头下标
		q->front = 0;
		//队尾下标
		q->rear = i;
	}
	//栈空等其他情况正常入队
	//队尾元素赋值
	q->data[q->rear] = data;
	//队尾移动到新位置
	q->rear = (q->rear + 1) % q->maxSize;
	return 1;
}
//打印队列从头到尾
int printfQueue(queue* q) {
	//处理传参问题
	if (q == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//判空
	int r = isEmpty(q);
	//为空
	if (r == 1) {
		printf("队空\n");
		return -1;
	}
	//其他情况正常打印
	//初始为队头下一个元素
	//遍历到队尾前一个元素
	int p = 0;
	for (p = q->front;p != (q->rear - 1 + q->maxSize) % q->maxSize;p = (p + 1) % q->maxSize) {
		printf("%d,", q->data[p]);
	}
	printf("%d\n", q->data[p]);
	return 1;
}
//出队
int Dequeue(queue* q, int* outData) {
	//处理传参问题
	if (q == NULL || outData == NULL) {
		printf("传参为空\n");
		return -1;
	}
	int res = isEmpty(q);
	//队空
	if (res == 1) return -1;
	//其他情况正常处理
	//保存元素值
	*outData = q->data[q->front];
	//移动队头
	q->front = (q->front + 1) % q->maxSize;
	return 1;
}
//读取队首元素
int getFront(queue* q, int* outData) {
	//处理传参问题
	if (q == NULL || outData == NULL) {
		printf("传参为空\n");
		return -1;
	}
	int res = isEmpty(q);
	//队空
	if (res == 1) return -1;
	//其他情况正常处理
	//保存元素值
	*outData = q->data[q->front];
	return 1;
}
//清空队列，不释放内存
int queueClear(queue* q) {
	//处理传参问题
	if (q == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//清空
	q->front = 0;
	q->rear = 0;
	return 1;
}