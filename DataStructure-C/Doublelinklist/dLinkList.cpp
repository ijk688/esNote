#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
	int data;
	//指向前驱节点
	struct Node* prev;
	//指向后继节点
	struct Node* next;
}node;

node* nCreate(int data);
int nDestroy(node** n);
int isEmpty(node* head);
int dllAddtail(node* head, int data);
void printfDll(node* head);
int dllDestroy(node** head);
int getNum(node* head);
int dllAddhead(node* head, int data);
int dllAddsp(node* head, int place, int data);
int dllDelsp(node* head, int place);
int dllDelfirst(node* head, int value);
int dllDellast(node* head, int value);
int dllDelall(node* head, int value);
int dllFindsp(node* head, int place, int* num);
int dllFindfirst(node* head, int value);
int dllFindlast(node* head, int value);
int dllFindall(node* head, int value, int** num);
 





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int main() {
	node* head = nCreate(0);
	int res = 0;
	//res = dllAddtail(head, 4);
	//res = dllAddtail(head, 1);
	//res = dllAddtail(head, 2);
	//res = dllAddtail(head, 4);
	//res = dllAddtail(head, 3);
	//res = dllAddtail(head, 4);
	//res = dllAddtail(head, 4);
	//res = dllDelfirst(head, 4);
	//res = dllDellast(head, 4);
	//res = dllDelsp(head, 3);
	//res = dllDelall(head, 4);
	//res = dllAddhead(head, 1);
	//res = dllAddhead(head, 2);
	//res = dllAddhead(head, 3);
	//res = dllAddhead(head, 4);
	//res = dllAddsp(head, 1, 5);
	int first = dllFindfirst(head, 4);
	int last = dllFindlast(head, 4);
	int* num;
	int all = dllFindall(head, 4,&num);
	if (first > 0) {
		printf("第一个找到的元素位置为：%d\n",first);
	}
	if (last > 0) {
		printf("最后一个找到的元素位置为：%d\n",last);
	}
	if (all > 0) {
		for (int i = 0;i < all;i++) {
			printf("第%d个元素位置为：%d\n", i + 1, *(num + i));
		}
		free(num);
	}
 
	int e = getNum(head);
	if (e >= 0) printf("双链表中一共%d个有效元素\n", e);
	if (res > 0) {
		printfDll(head);
	}
	int r = dllDestroy(&head);
	if (r > 0) printf("销毁了%d个节点\n", r);
	return 0;
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////









//查
//根据指定位置查值
int dllFindsp(node* head, int place, int* num) {
	//处理传参问题
	if (place <= 0) {
		printf("给定位置超出最小值范围\n");
		return -1;
	}
	int r = isEmpty(head);
	if (r == -1) return -1;
	//链表为空，无法查找有效值
	else if (r == 1) return -1;
	int e = getNum(head);
	if (place > e) {
		printf("给定值超出范围最大值\n");
		return -1;
	}
	//正常情况
	//循环place次，指向该值，并返回
	node* p = head;
	for (int i = 0;i < place;i++) {
		p = p->next;
	}
	//p指向该位置
	*num = p->data;
	return 1;
}
//根据值，查找第一个位置
int dllFindfirst(node* head, int value) {
	//处理传参问题
	int r = isEmpty(head);
	if (r == -1) return -1;
	//链表为空，无法查找有效值
	else if (r == 1) return -1;
	//正常情况
	//前置移位包含为节点，循环有效元素个数
	node* p = head;
	int count = 0;
	while (p->next != NULL) {
		p = p->next;
		count++;
		if (p->data == value) {
			//返回位置
			return count;
		}
	}
	//遍历结束仍未找到
	return 0;
}
//根据值，查找最后一个位置
int dllFindlast(node* head, int value) {
	//处理传参问题
	int r = isEmpty(head);
	if (r == -1) return -1;
	//链表为空，无法查找有效值
	else if (r == 1) return -1;
	//正常情况
	//前置移位包含为节点，循环有效元素个数
	//刷新出最后一个位置
	int count = 0;
	int last = 0;
	node* p = head;
	while (p->next != NULL) {
		p = p->next;
		count++;
		if (p->data == value) {
			last = count;
		}
	}
	//遍历结束返回位置
	return last;
}
//根据值，查找所有位置
//使用二级指针存放找到的所有位置
int dllFindall(node* head, int value, int** num) {
	//处理传参问题
	if (num == NULL) {
		printf("传入指针为空\n");
		return -1;
	}
	int r = isEmpty(head);
	if (r == -1) return -1;
	//链表为空，无法查找有效值
	else if (r == 1) return -1;
	//正常情况
	//前置移位包含为节点，循环有效元素个数
	//为二级指针解引用进行动态内存分配
	int e = getNum(head);
	*num = (int*)malloc(sizeof(int) * e);
	if (*num == NULL) {
		printf("动态内存分配失败\n");
		return -1;
	}
	node* p = head;
	int count = 0;
	int i = 0;
	while (p->next != NULL) {
		p = p->next;
		count++;
		if (p->data == value) {
			*(*num + i) = count;
			i++;
		}
	}
	//无匹配值直接释放内存
	if (i == 0) {
		free(*num);
		*num == NULL;
	}
	//遍历结束,返回查找的元素数量
	return i;
}
//删
//指定位置删除
int dllDelsp(node* head, int place) {
	//处理传参问题
	if (place <= 0) {
		printf("给定位置超出范围最小值\n");
		return -1;
	}
	int r = isEmpty(head);
	if (r == -1) return -1;
	//只有一个头节点
	else if (r == 1) return -1;
	int e = getNum(head);
	if (place > e) {
		printf("给定范围超出范围最大值\n");
		return -1;
	}
	//存在多个节点
	node* p = head;
	//循环place次，指向待删除节点位置
	for (int i = 0;i < place;i++) {
		p = p->next;
	}
	//删除逻辑
	//前驱指向后继，后继指向前驱
	//保存p的地址
	//特殊情况未最后一个节点
	if (place == e) {
		p->prev->next = NULL;
	}
	else {
		p->next->prev = p->prev;
		p->prev->next = p->next;
	}
	free(p);
	return 1;
}
//指定值，删除第一个值
int dllDelfirst(node* head, int value) {
	//处理传参问题
	int r = isEmpty(head);
	if (r == -1) return -1;
	//链表为空，无可删除的有效值
	else if (r == 1) return -1;
	//遍历找值
	//不包含head,循环有效值个数即可
	//跳过头节点
	node* p = head->next;
	while (p->next != NULL) {
		//判断
		if (p->data == value) {
			//删除
			p->next->prev = p->prev;
			p->prev->next = p->next;
			free(p);
			return 1;
		}
		p = p->next;
	}
	//遍历结束p未末位指针，在进行判断
	if (p->data == value) {
		//删除
		p->prev->next = NULL;
		free(p);
		return 1;
	}
	//结束
	return 0;
}
//指定值，删除最后一个值
int dllDellast(node* head, int value) {
	//处理传参问题
	int r = isEmpty(head);
	if (r == -1) return -1;
	//链表为空，无可删除的有效值
	else if (r == 1) return -1;
	//遍历找值
	//两种方式
	//遍历到尾部从尾部重新寻找
	//遍历到尾部，刷新地址，完成删除
	//显然第二种更优
	node* p = head;
	node* n = NULL;
	//跳过头节点，循环有效元素个数
	while (p->next != NULL) {
		//前置移位，包含末尾节点
		p = p->next;
		if (p->data == value) {
			//刷新n指针
			n = p;
		}
	}
	//遍历结束，判断n,p此时指向末尾节点
	//没找到
	if (n == NULL) return  0;
	else if (n == p) {
		p->prev->next = NULL;
		free(p);
		return 1;
	}
	else {
		n->next->prev = n->prev;
		n->prev->next = n->next;
		free(n);
		return 1;
	}
}
//指定值，删除所有值
int dllDelall(node* head, int value) {
	//处理传参问题
	int r = isEmpty(head);
	if (r == -1) return -1;
	//链表为空，无可删除的有效值
	else if (r == 1) return -1;
	//遍历判断，查到即删除
	//循环有效元素个数，后置移位不包含末尾节点
	//结束时p应指向末尾节点
	int count = 0;
	node* p = head->next;
	node* n = NULL;
	while (p->next != NULL) {
		if (p->data == value) {
			n = p;
			p->next->prev = p->prev;
			p->prev->next = p->next;
			p = n->next;
			free(n);
			count++;
		}
		else p = p->next;
	}
	//遍历结束，判断p
	if (p->data == value) {
		p->prev->next = NULL;
		free(p);
		count++;
	}
	return count;
}
//指定位置增
int dllAddsp(node* head, int place, int data) {
	//处理传参问题
	int r = isEmpty(head);
	//*head为空
	if (r == -1) return -1;
	if (place <= 0) {
		printf("给定位置超出范围最小值\n");
		return -1;
	}
	int e = getNum(head);
	if (e >= 0) {
		if (place > e + 1) {
			printf("给定位置超出范围最大值\n");
			return -1;
		}
	}
	else {
		printf("函数调用出错\n");
		return -1;
	}
	node* n = nCreate(data);
	//只有一个头节点
	if (r == 1) {
		head->next = n;
		n->prev = head;
		return 1;
	}
	//多个节点
	else {
		node* p = head;
		if (place == e + 1) {
			//需要一个尾部指针，循环N-1次
			while (p->next != NULL) {
				p = p->next;
			}
			//得到尾部指针p
			n->prev = p;
			p->next = n;
			return 1;
		}
		else {
			//需要移动到该位置
			//循环place次
			//推导：循环n-1次指针指向尾部，n-1即为有效元素个数
			//可得：循环place次，可达该位置
			for (int i = 0;i < place;i++) {
				p = p->next;
			}
			//得到当前位置的指针
			p->prev->next = n;
			n->prev = p->prev;
			n->next = p;
			p->prev = n;
			return 1;
		}
	}

}
//头增
int dllAddhead(node* head, int data) {
	//处理传参问题
	int res = isEmpty(head);
	//*head为空
	if (res == -1) return -1;
	//只有一个头结点
	node* n = nCreate(data);
	if (res == 1) {
		head->next = n;
		n->prev = head;
		return 1;
	}
	//多个节点
	else {
		n->next = head->next;
		head->next->prev = n;
		n->prev = head;
		head->next = n;
		return 1;
	}
}
//获取元素个数
int getNum(node* head) {
	//处理传参问题
	if (head == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//遍历得到有效元素个数
	int count = 0;
	node* p = head;
	//循环N-1次，结束指向NULL
	while (p->next != NULL) {
		p = p->next;
		count++;
	}
	return count;
}
//正序打印遍历
void printfDll(node* head) {
	if (isEmpty(head) == -1) {
		printf("传参为空\n");
		return;
	}
	if (isEmpty(head) == 1) {
		printf("链表为空");
		return;
	}
	node* p = head->next;
	while (p->next != NULL) {
		printf("%d,", p->data);
		p = p->next;
	}
	/*p此时指向最后一个节点*/
	printf("%d\n", p->data);
}
//销毁链表
//传参使用一级指针仅可销毁内存，不可悬空指针
//优先使用二级指针
int dllDestroy(node** head) {
	if (head == NULL) {
		printf("二级指针传参为空\n");
		return -1;
	}
	int res = isEmpty(*head);
	if (res == -1) {
		printf("传参为空\n");
		return -1;
	}
	//存在节点
	int count = 0;
	node* p = *head;
	node* n = NULL;
	//依次销毁
	while (p != NULL) {
		n = p;
		p = p->next;
		free(n);
		count++;
	}
	//头指针是外部可见的，可操作的入口指针
	*head = NULL;
	//返回销毁的节点数量
	return count;
}
//创建节点
node* nCreate(int data) {
	//动态内存分配
	node* n = (node*)malloc(sizeof(node));
	if (n == NULL) {
		printf("动态内存分配失败\n");
		return NULL;
	}
	n->prev = NULL;
	n->next = NULL;
	n->data = data;
	return n;
}
//销毁节点
int nDestroy(node** n) {
	//处理传参
	if (n == NULL || *n == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//销毁、
	// 非必要
	//(*n)->prev = NULL;
	//(*n)->next = NULL;
	//大前提是规范化创建节点
	free(*n);
	//悬空指针
	*n = NULL;
	return 0;
}
//判空
int isEmpty(node* head) {
	//处理传参
	if (head == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//带头双链表
	if (head->next == NULL) {
		return 1;
	}
	//否则头节点指向其他有效节点
	return 0;
}
//尾增
int dllAddtail(node* head, int data) {
	//不存在头节点
	int res = isEmpty(head);
	if (res == -1) {
		printf("head为空\n");
		return -1;
	}
	//存在头节点
	node* n = nCreate(data);
	//只存在一个头节点
	if (res == 1) {
		head->next = n;
		n->prev = head;
		return 1;
	}
	//存在多个节点
	node* p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	//遍历结束，p为最后节点
	p->next = n;
	n->prev = p;
	return 1;

}