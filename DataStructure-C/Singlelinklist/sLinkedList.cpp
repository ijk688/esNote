#include<stdio.h>
#include<stdlib.h>
#define MAX 10000
typedef struct Node {
	int data;
	Node* next;
}node;
//动态结构（如链表、树、图）：通常需要动态内存分配。
//堆内存：一块 struct Node 结构体（真正节点）
//↓
//指针变量：存该结构体首地址（用来找到节点）
//↓
//代码：p->data p->next 操作节点内容
 
node* nCreate(int data);
void nDestroy(node** n);
void sllDestroy(node** n);
int isEmpty(node* head);
int getNum(node* head, int* num);
void printfSll(node* head);
void sllAddhead(node** head, int data);
void sllAddtail(node** head, int data);
void sllAddsp(node** head, int place, int data);
void sllDelsp(node** head, int place);
void sllDelfirst(node** head, int data);
void sllDellast(node** head, int data);
void sllDelall(node** head, int data);
int sllModifysp(node* head, int place, int data);
int sllModifyfirst(node* head, int value, int data);
int sllModifylast(node* head, int value, int data);
int sllModifyall(node* head, int value, int data);
int sllFindsp(node* head, int place, int* value);
int sllFindfirst(node* head, int value, int* place);
int sllFindlast(node* head, int value, int* place);
int sllFindall(node* head, int value, int** place);
 









////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main() {
	//nCreate(1)返回一个地址，为右值
	//无法进行取值操作
	node* head=NULL;//空链表
	//node* head1 = nCreate(2);
	//head->next = head1;\
	sllAddtail(&head, 2);
	//sllAddhead(&head, 6);
	//sllAddhead(&head, 6);
	sllAddtail(&head, 7);
	sllAddtail(&head, 7);
	sllAddtail(&head, 7);
	sllAddtail(&head, 7);
	sllAddtail(&head, 1);
	sllAddtail(&head, 2);
	sllAddtail(&head, 3);
	sllAddtail(&head, 7);
	sllAddtail(&head, 5);
	int value = 0;
	int place = 0;
	int* place1=NULL;
	//if (!sllFindsp(head, 1, &value)) {
	//	printf("value:%d\n", value);
	//}
	//if (sllFindfirst(head, 7, &place)==1) {
	//	printf("place:%d\n", place);
	//}
	// if (sllFindlast(head, 7, &place)==1) {
	//	printf("place:%d\n", place);
	//}
	int res = sllFindall(head, 7, &place1);
	if ( res>0) {
		printf("总共查到%d个结果\n", res);
		for (int i = 0;i < res;i++) {
			printf("第%d个查找值的位置为%d\n", i + 1, *(place1 + i));
		}
	   }
	free(place1);
	//sllDelall(&head, 2);
	//if (sllModifysp(head, 1, 6)) return 0;
	//if (sllModifyfirst(head, 5, 7)) return 0;
	//if (sllModifylast(head, 7, 8)) return 0;
	//if (sllModifyall(head, 7, 8)) return 0;
 
	int num = -1;
	//int* num = (int*)malloc(sizeof(int));
 
	if (getNum(head, &num)) {
		printf("num:%d\n", num);
	}
	//getNum(head, num);
    
	printfSll(head);
	//nDestroy()
	//nDestroy(&n1);
	sllDestroy(&head);
	return 0;
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////









//查找
//根据位置查找值
int sllFindsp(node* head, int place, int* value) {
	//处理传参错误
	if (head == NULL || value == NULL) {
		printf("传参为空\n");
		return -1;
	}
	if (place <= 0) {
		printf("给定位置超出范围最小值\n");
		return -1;
	}
	int num = -1;
	if (getNum(head, &num)) {
		if (place > num) {
			printf("给定位置超出范围最大值\n");
			return -1;
		}
		//查找逻辑
		node* p = head;
		for (int i = 1;i < place;i++) {
			p = p->next;
		}
		*value = p->data;
		return 1;
	}
	else return -1;

}
//根据值查找第一个位置
int sllFindfirst(node* head, int value, int* place) {
	//处理传参错误
	if (head == NULL || place == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//查找逻辑
	int res = 0;
	node* p = head;
	while (p != NULL) {
		res++;
		if (p->data == value) {
			*place = res;
			return 1;
		}
		p = p->next;
	}
	//遍历结束仍未找到
	return 0;

}
//根据值查找最后一个位置
int sllFindlast(node* head, int value, int* place) {
	//处理传参错误
	if (head == NULL || place == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//查找逻辑
	int count = 0;
	node* p = head;
	while (p != NULL) {
		count++;
		if (p->data == value) {
			*place = count;
		}
		p = p->next;
	}
	//最后判断
	if (count == 0) return 0;
	else {
		return 1;
	}
}
//根据值查找所有位置
int sllFindall(node* head, int value, int** place) {
	//处理传参错误
	if (head == NULL || place == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//查找逻辑
	int num = -1;
	if (getNum(head, &num)) {
		*place = (int*)malloc(sizeof(int) * num);
		if (*place == NULL) {
			printf("动态内存分配失败\n");
			return -1;
		}
	}
	else return -1;
	int i = 0;
	int j = 0;
	node* p = head;
	while (p != NULL) {
		i++;
		if (p->data == value) {
			*(*place + j) = i;
			j++;
		}
		p = p->next;
	}
	//未查到目标释放内存
	if (j == 0) free(place);
	return j;
}
//修改功能
// 全部采用int类型函数
// 默认返回0代表成功，返回正数代表操作数量
// 返回负数代表未成功执行
//根据位置修改
int sllModifysp(node* head, int place, int data) {
	//处理传参错误
	if (head == NULL) {
		printf("传参为空\n");
		return -1;
	}
	if (place <= 0) {
		printf("给定位置超出范围最小值\n");
		return -1;
	}
	int num = -1;
	if (getNum(head, &num)) {
		if (place > num) {
			printf("给定位置超出范围最大值\n");
			return -1;
		}
		//开始按位修改
		node* p = head;
		for (int i = 1;i < place;i++) {
			p = p->next;
		}
		p->data = data;
		return 0;
	}
}
//根据值修改，修改遇到的第一个值
int sllModifyfirst(node* head, int value, int data) {
	//处理传参错误
	if (head == NULL) {
		printf("传参错误\n");
		return -1;
	}
	//修改逻辑
	node* p = head;
	//其次遍历判断后续节点的情况
	//包含头尾节点，但不包含只有一个头节点的情况
	while (p != NULL) {
		if (p->data == value) {
			p->data = data;
			return 0;
		}
		p = p->next;
	}
	//遍历结束无返回值证明未找到
	return -1;
}
//根据值修改，修改遇到的最后一个值
int sllModifylast(node* head, int value, int data) {
	//处理传参错误
	if (head == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//修改逻辑
	//遍历处理其余情况，采取优先级思想
	//直接记住指针即可
	node* n = NULL;
	node* p = head;
	while (p != NULL) {
		if (p->data == value) {
			n = p;
		}
		p = p->next;
	}

	//未得到无匹配值
	if (n == NULL) return -1;
	//得到最大优先级数据对其进行修改
	else {
		n->data = data;
		return 0;
	}
}
//根据值修改，修改遇到的所有值
int sllModifyall(node* head, int value, int data) {
	//处理传参问题
	if (head == NULL) {
		printf("传参为空\n");
		return -1;
	}
	//修改逻辑
	//处理常规情况
	node* p = head;
	while (p != NULL) {
		if (p->data == value) {
			p->data = data;
		}
		p = p->next;
	}
	//遍历结束
	return 0;
}
//实现删除功能四个
//指定位置删除
void sllDelsp(node** head, int place) {
	if (head == NULL) {
		printf("传参为空\n");
		return;
	}
	//给定的单链表存在且为空
	if (isEmpty(*head)) {
		printf("单链表为空，显然没有可删除元素\n");
		return;
	}
	//给定位置明显不合理
	if (place <= 0) {
		printf("给定值超出范围最小值\n");
		return;
	}
	int num = -1;
	if (getNum(*head, &num)) {

		//给定位置明显不合理
		if (place > num) {
			printf("给定值超出范围最大值\n");
			return;
		}
		node* n = NULL;
		//给定位置合理可进行删除操作
		//给定位置为第一个位置
		if (place == 1) {
			//删除操作时应释放节点内存
			n = *head;
			*head = (*head)->next;
			free(n);
		}
		//给定位置为最后一个位置
		else if (place == num) {
			node* newtail = *head;
			while ((newtail->next)->next != NULL) {
				newtail = newtail->next;
			}
			n = newtail->next;
			newtail->next = NULL;
			free(n);
		}
		//给定位置为中间位置
		else {
			node* p = *head;
			for (int i = 1;i < place - 1;i++) {
				p = p->next;
			}
			n = p->next;
			p->next = p->next->next;
			free(n);

		}

	}
	else {
		printf("获取元素个数失败\n");
		return;
	}

}
//指定值删除删除遇到的第一个值
void sllDelfirst(node** head, int data) {
	if (head == NULL) {
		printf("传参为空\n");
		return;
	}
	if (isEmpty(*head)) {
		printf("单链表为空，无可删除元素\n");
		return;
	}
	//遍历整个链表，直至发现所删值停止并执行删除操作
	//首先判断头节点是否为可删除节点
	node* n = NULL;
	if ((*head)->data == data) {
		n = *head;
		*head = (*head)->next;
		free(n);
		return;
	}
	node* p = *head;
	//之后判断除头节点,尾节点以外的节点
	while (p->next != NULL) {
		if (p->next->data != data) p = p->next;
		else {
			n = p->next;
			p->next = p->next->next;
			free(n);
			return;
		}
	}
	//如果以上条件都没有成立
	printf("未找到所输入的元素，无法执行删除操作\n");

}
//指定值删除删除遇到的最后一个值
void sllDellast(node** head, int data) {
	if (head == NULL) {
		printf("传参为空\n");
		return;
	}
	if (isEmpty(*head)) {
		printf("单链表为空，无可删除元素\n");
		return;
	}
	//由于单链表很难采取倒序操作
	//采用优先级思想，依旧使用正序遍历
	//当前节点的前驱
	node* prep = NULL;
	//最后一个节点的前驱
	node* prelast = NULL;
	//最后一个节点
	node* last = NULL;
	//当前节点
	node* p = *head;
	while (p != NULL) {
		if (p->data == data) {
			last = p;
			prelast = prep;
		}
		p = p->next;
		prep = p;
	}
	if (last == NULL) {
		printf("单链表中无删除的指定元素\n");
		return;
	}
	//最后一个为头节点无前驱
	if (last == *head) {
		*head = (*head)->next;
	}
	else {
		prelast->next = last->next;
	}
	free(last);
}
//指定值删除删除遇到的所有值
void sllDelall(node** head, int data) {
	if (head == NULL) {
		printf("传参为空\n");
		return;
	}
	if (isEmpty(*head)) {
		printf("单链表为空，无可删除元素\n");
		return;
	}

	int res = 1;
	//采用常规正序遍历
	node* n = NULL;
	//删除所有符合条件的头节点
	while (*head != NULL && (*head)->data == data) {
		n = *head;
		*head = (*head)->next;
		free(n);
		res = 0;
	}
	//处理符合条件的非头节点
	node* p = *head;
	while (p != NULL && p->next != NULL) {
		if (p->next->data == data) {
			n = p->next;
			p->next = p->next->next;
			free(n);
			res = 0;
			continue;
		}
		p = p->next;
	}
	if (res) {
		printf("单链表中无给定元素，无法执行删除操作\n");
		return;
	}
}
//增：头增，尾增，指定位置增
// 指定位置插入
void sllAddsp(node** head, int place, int data) {
	if (head == NULL) {
		printf("传参为空\n");
		return;
	}
	if (place <= 0) {
		printf("输入值超出最小值边界\n");
		return;
	}
	//即使传参要求使用指针变量，可用局部变量加取址实现
	int num = -1;
	if (getNum(*head, &num)) {
		if (place > num + 1) {
			printf("输入值超出最大值边界\n");
			return;
		}
		node* n = nCreate(data);
		if (place == 1) {
			n->next = *head;
			*head = n;
		}
		else if (place == num + 1) {
			node* tail = *head;
			while (tail->next != NULL) {
				tail = tail->next;
			}
			tail->next = n;
		}
		else {
			node* p = *head;
			while (place > 2) {
				place--;
				p = p->next;
			}
			n->next = p->next;
			p->next = n;
		}


	}
	else return;
}
//尾增
void sllAddtail(node** head, int data) {
	if (head == NULL) {
		printf("传参为空\n");
		return;
	}
	node* n = nCreate(data);
	//头节点为空
	if (*head == NULL) {
		*head = n;
	}
	//头节点不为空
	else {
		node* tail = *head;
		while (tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = n;
	}
}
//头增
void sllAddhead(node** head, int data) {
	//即使头节点为空也可头插
	if (head == NULL) {
		printf("传参为空\n");
		return;
	}
	node* n = nCreate(data);
	//疑惑点：为什么这一步不生效
	n->next = *head;
	//仅仅将新节点指向head,head节点并未发生改变
	//头插自然head节点变为新节点
	//由于需要修改一级指针变量
	//依次传参使用二级指针
	*head = n;
}
//链表销毁
//疑惑点：链表销毁对应的就是节点销毁
//但如果销毁一个节点又很难找到下一个节点
//解决方案：先保存下一个节点
void sllDestroy(node** head) {
	if (head == NULL || *head == NULL) {
		printf("传参为空\n");
		return;
	}
	node* p = *head;
	while (p != NULL) {
		node* q = p->next;
		free(p);
		p = q;
	}
	//悬空头指针
	*head = NULL;
}
//打印遍历
void printfSll(node* head) {
	if (isEmpty(head)) return;
	node* p = head;
	while (p->next != NULL) {
		printf("%d,", p->data);
		p = p->next;
	}
	printf("%d\n", p->data);
}
//判空
int isEmpty(node* head) {
	if (head == NULL) {
		//非系统错误
		//perror("传参为空");
		printf("头节点为空\n");
		return 1;
	}
	return 0;
}
//判满,单链表无需实现
//获取元素个数
int getNum(node* head, int* num) {
	if (head == NULL || num == NULL) {
		printf("传参为空\n");
		return 0;
	}
	//从0开始，遍历整张链表
	*num = 0;
	node* p = head;
	while (p != NULL) {
		(*num)++;
		p = p->next;
		//*num++语法错误！！！
	}
	return 1;
}
//单链表分为带头结点与不带头结点
//优先实现带头结点单链表
//node->data等价于(*node).data
//节点创建
node* nCreate(int data) {
	node* n = (node*)malloc(sizeof(node));
	if (n == NULL) {
		printf("节点创建失败\n");
		return NULL;
	}
	n->data = data;
	//next变量仅仅用来存储下一个结点的地址
	//无需动态内存分配
	n->next = NULL;
	return n;
}
//节点销毁
void nDestroy(node** n) {
	//二级指针需要两次判空
	if (n == NULL || *n == NULL) {
		printf("传参为空\n");
		return;
	}
	//这一步并没必要，释放内存后无意义
	//(*n)->next = NULL;
	//但结构体成员此前使用的是动态内存分配
	//需要前一步释放
	free(*n);
	*n = NULL;
}