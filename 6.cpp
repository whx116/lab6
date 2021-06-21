#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define NUM 50 //最大容量
int s1[NUM], s2[NUM],mid[15];
int cmp(const void * a, const void * b) {
	return *(int *)a - *(int *)b;
}
int select(int num[], int p, int r, int k) {
	//当前数组长度
	int len = r - p + 1;
	//判断长度是否小于5，小于5直接排序求第k小的数
	if (len <= 5) {
		qsort(num, len, sizeof(int), cmp);
		return num[k - 1];
	}
	else {
		//将数组分为group组，每组5个数
		int group = len / 5;
		int i;
		//将数组剩余的数赋值给m
		int m = len - group * 5;
		//每个group组进行快速排序
		for (i = 0; i < group; i++) {
			qsort(num + i * 5, 5, sizeof(int), cmp);
			//排序后，把每个group组的中间值放在mid中
			mid[i] = num[i * 5 + 2];
		}
		//若分完group组有剩余，将剩余的数进行排序
		if (m > 0) {
			qsort(num + group * 5, m, sizeof(int), cmp);
			//将中间值赋值给mid
			mid[group] = num[group * 5 + m / 2];
			//group+1
			group++;
		}
		//对mid数组排序，找出中间值赋值给mm
		qsort(mid, group, sizeof(int), cmp);
		int mm = mid[group / 2];
		//s1的长度为len_s1,s2的长度为len_s2
		int len_s1 = 0, len_s2 = 0;
		//用mm(整个数组最中间的值)把数组分为s1和s2
		for (int i = p-1; i < r; ++i) {
			//比mm小的数放在s1，比mm大的数放在s2
			if (num[i] < mm) {
				s1[len_s1++] = num[i];
			}
			else {
				s2[len_s2++] = num[i];
			}
		}
		int f = 0;
		//如果k的值==len_s1+1,说明mm就是第k小的数
		if (k == len_s1 + 1) {
			f = mm;
		}
		else if (k <= len_s1) {
			//如果k<=len_s1,说明第k小的数在s1,递归调用select函数
			f = select(s1, 1, len_s1, k);
		}
		else {
			//如果k>len_s1,说明第k小的数在s2,递归调用select函数
			f = select(s2, 1, len_s2, k - len_s1);
		}
		return f;
	}
}
int main() {
	//输入示例
	int n[NUM] = { 13,12,11,14,15,7,9,14,16,18,2,4,6,8,10,1,3,5,7,9,2,3};
	printf("%d\n", select(n, 1, 22, 10));
	return 0;
}
