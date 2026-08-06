#include<stdio.h>
#include<stdlib.h>
#define MAX 50
typedef struct SeqList {
	int* data;
	int size;
	//不能在定义是给成员赋值
	int max;
	//int state = 0;
}sl;
//if (s == NULL) {
//	printf("传参为空,函数终止\n");
//	return;
//}





sl* slCreate();
void slDestroy(sl** p);
int getSize(sl* s, int* n);
int isEmpty(sl* s);
int isFull(sl* s);
void slAdd1(sl* seqlist, int a);
void printfSl(sl* s);
void slAdd2(sl* seqlist, int a);
void slAdd3(sl* seqlist, int p,int a);
void slDel1(sl* seqlist);
void slDel2(sl* seqlist);
void slDel3(sl* seqlist,int p);
void slDelfirst(sl* s, int v);
void slDellast(sl* s, int v);
void slDelall(sl* s, int v);
void slModifybyp(sl* s, int p, int value);
void slModifybyfirst(sl* s, int v, int value);
void slModifybylast(sl* s, int v, int value);
void slModifybyall(sl* s, int v, int value);
int slFindbyp(sl* seqlist,int* q,int p);
int slFindbyfirstv(sl* seqlist, int* p, int value);
int slFindbylastv(sl* seqlist, int* p, int value);
int slFindbyallv(sl* seqlist, int** p, int* q, int value);











////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int main() {
	//遗忘点：动态数组的创建。
	//char* str;
	//str = (char*)malloc(MAX * sizeof(char));
	//*str = '\0';
	//if (str == NULL) {
	//	return 0;
	//}
	sl* sl1 = slCreate();
	//slAdd1(sl1, 1);
	//slAdd1(sl1, 2);
	//slAdd1(sl1, 3);
	//slAdd1(sl1, 4);
	//slAdd1(sl1, 5);
	//slAdd1(sl1, 6);
	slAdd1(sl1, 1);
	slAdd1(sl1, 2);
	slAdd1(sl1, 1);
	slAdd1(sl1, 1);
	slAdd1(sl1, 3);
	slAdd1(sl1, 1);
	slAdd1(sl1, 1);
	slAdd1(sl1, 1);
	printfSl(sl1);
	//slDelfirst(sl1, 3);
	//slDellast(sl1, 1);
	slDelall(sl1, 1);
	printfSl(sl1);
 
 
	
	//无需创建二级指针，&sl1既可作为二级指针参数
	slDestroy(&sl1);
	if (sl1 ==NULL) {
		printf("顺序表销毁成功\n");
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////















//按值删除，删除匹配到的第一个元素
void slDelfirst(sl* s, int v) {
	//冗余变量！！！
	//int p=1;
	if (s == NULL) {
		printf("传参为空,函数终止\n");
		return;
	}
	if (isEmpty(s)) {
		printf("顺序表中无元素，函数终止\n");
		return;
	}
	for (int i = 0;i < s->size;i++) {
		if (*(s->data + i) == v) {
			slDel3(s, i + 1);
			return;
		}
	}

	printf("顺序表中无该元素，函数终止\n");
	return;
}
//按值删除，删除匹配到的最后一个元素
void slDellast(sl* s, int v) {
	if (s == NULL) {
		printf("传参为空,函数终止\n");
		return;
	}
	if (isEmpty(s)) {
		printf("顺序表中无元素，函数终止\n");
		return;
	}
	for (int i = s->size - 1;i >= 0;i--) {
		if (*(s->data + i) == v) {
			slDel3(s, i + 1);
			return;
		}
	}
	printf("顺序表中无该元素，函数终止\n");
	return;
}
//按值删除，删除匹配到的所有元素
void slDelall(sl* s, int v) {
	if (s == NULL) {
		printf("传参为空,函数终止\n");
		return;
	}
	if (isEmpty(s)) {
		printf("顺序表中无元素，函数终止\n");
		return;
	}
	int p = 0;
	int a = s->size;
	while (a--) {
		if (*(s->data + p) == v) {
			slDel3(s, p + 1);
		}
		else {
			p++;
		}
	}
}
//第四个功能：修改
//非两大类，按值修改，按位置修改
//按值修改下分三种方法
//修改遇到的第一个值
//修改最后一个值
//修改所有的值
//按位修改
void slModifybyp(sl* s, int p, int value) {
	if (s == NULL) {
		printf("传参为空,函数终止\n");
		return;
	}
	//顺序表中无值
	if (isEmpty(s)) {
		printf("顺序表中无元素，函数终止\n");
		return;
	}
	if (p <= 0) {
		printf("修改位置小于最小值，函数终止\n");
		return;
	}
	if (p > s->size) {
		printf("修改位置大于最大值，函数终止\n");
		return;
	}
	*(s->data + p - 1) = value;
}
//按值修改，修改遇到的第一个值
void slModifybyfirst(sl* s, int v, int value) {
	if (s == NULL) {
		printf("传参为空,函数终止\n");
		return;
	}
	//顺序表中无值
	if (isEmpty(s)) {
		printf("顺序表中无元素，函数终止\n");
		return;
	}
	for (int i = 0;i < s->size;i++) {
		if (*(s->data + i) == v) {
			*(s->data + i) = value;
			return;
		}
	}
	printf("遍历结束，无匹配元素\n");
	return;
}
void slModifybylast(sl* s, int v, int value) {
	if (s == NULL) {
		printf("传参为空,函数终止\n");
		return;
	}
	//顺序表中无值
	if (isEmpty(s)) {
		printf("顺序表中无元素，函数终止\n");
		return;
	}
	for (int i = s->size - 1;i >= 0;i--) {
		if (*(s->data + i) == v) {
			*(s->data + i) = value;
			return;
		}
	}
	printf("遍历结束，无匹配元素\n");
	return;
}
void slModifybyall(sl* s, int v, int value) {
	if (s == NULL) {
		printf("传参为空,函数终止\n");
		return;
	}
	//顺序表中无值
	if (isEmpty(s)) {
		printf("顺序表中无元素，函数终止\n");
		return;
	}
	int num = 0;
	for (int i = 0;i < s->size;i++) {
		if (*(s->data + i) == v) {
			*(s->data + i) = value;
			num++;
		}
	}
	printf("遍历结束，共修改%d个元素\n", num);
}
//打印遍历
void printfSl(sl* seqlist) {
	if (seqlist == NULL) {
		printf("传参为空,函数终止\n");
		return;
	}
	if (isEmpty(seqlist)) {
		printf("顺序表为空，函数终止\n");
		return;
	}
	printf("数据结构名称：seqlist\n");
	printf("该顺序表最大值为：%d\n", seqlist->max);
	printf("该顺序表当前存储的元素个数为：%d\n", seqlist->size);
	printf("具体元素如下\n");
	for (int i = 0;i < seqlist->size - 1;i++) {
		printf("%d,", *(seqlist->data + i));
	}
	printf("%d\n", *(seqlist->data + seqlist->size - 1));
}
//获取元素个数
int getSize(sl* seqlist, int* num) {
	//注意：水杯指针需进行判空操作
	if (seqlist == NULL || num == NULL) {
		printf("传参为空，函数终止\n");
		return 0;
	}
	*num = seqlist->size;
	return 1;
}
//判空
//传入参数为空 -1
//传入参数不为空，结构内容为空 1
//传入参数不为空，结构内容不为空 0
int isEmpty(sl* seqlist) {
	if (seqlist == NULL) {
		printf("传参为空，函数终止\n");
		return -1;
	}
	//精简写法
	return seqlist->size == 0 ? 1 : 0;
	//if (seqlist->size == 0) return 1;
	//if (seqlist->size > 0) return 0;
	//return -1;
}
//判满
//传入参数为空 -1
//传入参数不为空，结构内容为满 1
//传入参数不为空，结构内容不满 0
int isFull(sl* seqlist) {
	if (seqlist == NULL) {
		printf("传参为空，函数终止\n");
		return -1;
	}
	return seqlist->size == seqlist->max ? 1 : 0;
	//if (seqlist->size == seqlist->max) return 1;
	//if (seqlist->size < seqlist->max) return 0;
	//return -1;

}
//销毁
void slDestroy(sl** seqlist) {
	if (seqlist == NULL || *seqlist == NULL) {
		printf("传参为空，函数终止\n");
		return;
	}
	//在销毁操作中使用到了free()释放内存函数
	//该函数只能用于释放指向堆内存空间的指针
	//而不能用于释放指向栈内存空间的指针
	//例如：sl str;free(&str),错误！！！
	//所以就不能直接在函数内部free
	//需要函数外手动free
	//而栈内存，函数结束会自动释放
	//使用前还用进行判空操作
	//free(seqlist);
	if ((*seqlist)->data != NULL) {
		free((*seqlist)->data);
		//规范，悬空指针
		(*seqlist)->data = NULL;
	}
	//先置空在销毁，free(NULL)无任何操作
	free(*seqlist);
	//使用二级指针即可实现置空操作
	*seqlist = NULL;
}
//第三个功能：查找
//查找分两个类，按值查找，按位置查找
//按值查找分：
//输出第一个值的位置||最后一个值的位置||所有值的位置

//按值查找，输出所有值的位置
//如果所有值都为该值，那位置最大就是size，存储位置的数组大小至少为size+1
//疑惑点：函数接受的参数不固定，数组大小不固定，我认为函数内部应该重新分配数组空间
//疑惑点：向用户传递了一个不知大小的数组
//两种解决方法：函数内printf告知用户数组大小
//使用指针将数组大小传出
//疑惑点：如果用以及指针作为传输数组的工具则会发生以下情况
//一般情况下，函数内外指针的区别是指向同一地址的不同变量
//所以通过函数内解引用可以让函数外也可以接受到值
// 这就是水杯指针的本质
//函数内指针指向数组正确，因为使用的是新创建的指针
//函数外指针指向垃圾值，因为函数外指针无法接受函数内创建的指针
//函数外指针始终指向垃圾值
//函数内指针先是指向垃圾值，后面重定向为新创建的数组地址
//解决方案，既然改不了函数外指针地址，那就改指针地址指向的内容
//由于指针地址指向的内容是指针，传参是需要使用二级指针
//依次类推，函数需要想向外改的为常规值，一级指针即可
//函数需要想向外改的为数组，需要用到二级指针
//函数需要想向外改的为二级指针，需要用到三级指针
int slFindbyallv(sl* seqlist, int** place, int* num, int value) {
	//有时，使用多级指针较为复杂，完全可以用一级指针接受多级指针解引用
	// 但最后要记住一定要回写地址！！！
	// 确保函数多级指针解引用（即函数外的内容）有所改动
	//传参指针进行判空操作
	if (seqlist == NULL || place == NULL || num == NULL) {
		printf("传参为空，函数终止\n");
		return 0;
	}
	//二级指针初始化后，原地址值可正常使用
	//但一级解引用是垃圾地址值，不可正常使用
	//同理，二级解引用依然不可正常使用
	*place = NULL;
	//创建新扩容的临时指针
	//不使用malloc而是用realloc
	//realloc多了一步数据检查
	//因为realloc在扩容时不会丢失原有数据，但这里体现的并不明显
	//bug:漏乘sizeof(int)
	int* tmp = (int*)realloc(*place, (seqlist->size + 1) * sizeof(int));
	//判空
	if (tmp == NULL) {
		printf("临时扩容指针为空，函数终止\n");
		return 0;
	}
	*place = tmp;
	int j = 0;
	for (int i = 0;i < seqlist->size;i++) {
		if (*(seqlist->data + i) == value) {
			*((*place) + j) = i + 1;
			printf("第%d个值的位置为：%d\n", i + 1, *((*place) + j));
			j++;
		}
	}
	*num = j;
	if (j) return 1;
	printf("遍历结束，顺序表中无该数据\n");
	return 0;
}
//按值查找：输出第一个值的位置
int slFindbyfirstv(sl* seqlist, int* place, int value) {
	//传参指针进行判空操作
	if (seqlist == NULL || place == NULL) {
		printf("传参为空，函数终止\n");
		return 0;
	}
	for (int i = 0;i < seqlist->size;i++) {
		if (*(seqlist->data + i) == value) {
			*place = i + 1;
			return 1;
		}
	}
	printf("遍历结束，顺序表中无此数据\n");
	return 0;
}
//按值查找：输出最后一个值的位置
int slFindbylastv(sl* seqlist, int* place, int value) {
	//传参指针进行判空操作
	if (seqlist == NULL || place == NULL) {
		printf("传参为空，函数终止\n");
		return 0;
	}
	for (int i = seqlist->size - 1;i >= 0;i--) {
		if (*(seqlist->data + i) == value) {
			*place = i + 1;
			return 1;
		}
	}
	printf("遍历结束，顺序表中无此数据\n");
	return 0;
}
//按位置查找
//难点：使用返回int类型函数时会出现return0的乌龙情况
//解决方案：返回结果表示是否查找成功
//难点：返回结果只有一个，没有接受值的载体
//解决方案：巧用指针，调用者传一个接受值的指针结果可通过引用指针看到
int slFindbyp(sl* seqlist, int* pint, int p) {
	//传参指针都要进行判空操作
	if (seqlist == NULL || pint == NULL) {
		printf("传参为空，函数终止\n");
		return 0;
	}
	if (seqlist->size == 0) {
		printf("顺序表中无数据，函数终止\n");
		return 0;
	}
	if (p <= 0) {
		printf("给定位置小于最小值，函数终止\n");
		return 0;
	}
	else if (p > seqlist->size) {
		printf("给定位置大于最大值，函数终止\n");
		return 0;
	}
	else {
		*pint = *(seqlist->data + p - 1);
		return 1;
	}
}
//第二个功能：删除
//有四种方法，头删，尾删，指定位置删，指定值删
//指定值删又分三种，第一个值删，最后一个值删，所有值删
//尾删
void slDel1(sl* seqlist) {
	//判断传参是否为空
	if (seqlist == NULL) {
		printf("传参为空，函数终止\n");
		return;
	}
	//难点：对于刚初始化成功的指针但无值不知如何判断
	//解决方法专门添加一个状态成员
	//显然根据size大小就可判断，不必多此一举
	if (seqlist->size == 0) {
		printf("该表中并无数据，无法进行删除操作\n");
		return;
	}
	//难点：如何删除特定节点的值
	//通过size确定顺序表边界，赋值不用管
	//既不是赋值垃圾，也不是free释放

	//尾部删除基本逻辑
	//*(seqlist->data + seqlist->size-1) = 0;
	seqlist->size--;
}
//头删
void slDel2(sl* seqlist) {
	if (seqlist == NULL) {
		printf("传参为空，函数终止\n");
		return;
	}
	if (seqlist->size == 0) {
		printf("该表中并无数据，无法进行删除操作\n");
		return;
	}

	//头删基本逻辑
	//注意先移位，在缩减长度，顺序颠倒导致数组越界
	//循环越界，最后一次循环：最后一个值=越界值
	for (int i = 0;i < seqlist->size - 1;i++) {
		*(seqlist->data + i) = *(seqlist->data + i + 1);
	}
	seqlist->size--;
}
//指定位置删
void slDel3(sl* seqlist, int p) {
	if (seqlist == NULL) {
		printf("传参为空，函数终止\n");
		return;
	}
	if (seqlist->size == 0) {
		printf("该表中并无数据，无法进行删除操作\n");
		return;
	}
	if (p <= 0||p>seqlist->size) {
		printf("给定值越界，函数终止\n");
		return;
	}
	else {
		for (int i = p - 1;i < seqlist->size - 1;i++) {
			*(seqlist->data + i) = *(seqlist->data + i + 1);
		}
		seqlist->size--;
	}
}
//顺序表的创建
sl* slCreate() {
	sl* seqlist = (sl*)malloc(sizeof(sl));
	if (seqlist == NULL) {
		printf("初始化失败，函数终止\n");
		return NULL;
	}
	seqlist->data = (int*)malloc(MAX * sizeof(int));
	if (seqlist->data == NULL) {
		printf("数组内存申请失败，函数终止\n");
		free(seqlist);
		return NULL;
	}
	seqlist->size = 0;
	seqlist->max = MAX;
	return seqlist;
}
//第一个功能：增，有三种方法，尾插，头插，指定位置插入
//尾插
void slAdd1(sl* seqlist, int a) {
	//前置判断防止传入空指针
	if (seqlist == NULL) {
		printf("传入空指针，函数终止\n");
		return;
	}
	if (seqlist->size >= seqlist->max) {
		printf("正在重新分配内存空间\n");
		//bug:扩容量固定，无法二次扩展
		//seqlist->data = (int*)realloc(seqlist->data, 2 * MAX);
		//seqlist->max = 2 * MAX;
		//realloc函数为了防止扩容时导致原有地址丢失采用临时地址
		//临时指针要接受源地址，realloc后补字节大小计算
		int* tmp;
		tmp = (int*)realloc(seqlist->data, 2 * seqlist->max * sizeof(int));
		if (tmp == NULL) {
			printf("数组内存申请失败，函数终止\n");
			return;
		}
		seqlist->data = tmp;
		seqlist->max = 2 * seqlist->max;
	}
	//尾插基本逻辑
	*(seqlist->data + seqlist->size) = a;
	seqlist->size++;
}
//头插
void slAdd2(sl* seqlist, int a) {
	//前置判断防止传入空指针
	if (seqlist == NULL) {
		printf("传入空指针，函数终止\n");
		return;
	}
	if (seqlist->size >= seqlist->max) {
		printf("正在重新分配内存空间\n");
		//bug:扩容量固定，无法二次扩展
		//seqlist->data = (int*)realloc(seqlist->data, 2 * MAX);
		//seqlist->max = 2 * MAX;
		//realloc函数为了防止扩容时导致原有地址丢失采用临时地址
		//临时指针要接受源地址，realloc后补字节大小计算
		int* tmp;
		tmp = (int*)realloc(seqlist->data, 2 * seqlist->max * sizeof(int));
		if (tmp == NULL) {
			printf("数组内存申请失败，函数终止\n");
			return;
		}
		seqlist->data = tmp;
		seqlist->max = 2 * seqlist->max;
	}
	//头插基本逻辑
	for (int i = seqlist->size;i >= 1;i--) {
		*(seqlist->data + i) = *(seqlist->data + i - 1);
	}
	*(seqlist->data) = a;
	seqlist->size++;
}
//指定位置插入
void slAdd3(sl* seqlist, int p, int a) {
	//前置判断防止传入空指针
	if (seqlist == NULL) {
		printf("传入空指针，函数终止\n");
		return;
	}
	if (seqlist->size >= seqlist->max) {
		printf("正在重新分配内存空间\n");
		//bug:扩容量固定，无法二次扩展
		//seqlist->data = (int*)realloc(seqlist->data, 2 * MAX);
		//seqlist->max = 2 * MAX;
		//realloc函数为了防止扩容时导致原有地址丢失采用临时地址
		//临时指针要接受源地址，realloc后补字节大小计算
		int* tmp;
		tmp = (int*)realloc(seqlist->data, 2 * seqlist->max * sizeof(int));
		if (tmp == NULL) {
			printf("数组内存申请失败，函数终止\n");
			return;
		}
		seqlist->data = tmp;
		seqlist->max = 2 * seqlist->max;
	}
	//基本逻辑
	if (p > seqlist->size||p<=0) {
		printf("给定值越界，函数终止\n");
		return;
	}
	else {
		for (int i = seqlist->size;i >= p;i--) {
			*(seqlist->data + i) = *(seqlist->data + i - 1);
		}
		*(seqlist->data + p - 1) = a;
		seqlist->size++;

	}
}