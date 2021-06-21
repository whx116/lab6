#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define NUM 50 //�������
int s1[NUM], s2[NUM],mid[15];
int cmp(const void * a, const void * b) {
	return *(int *)a - *(int *)b;
}
int select(int num[], int p, int r, int k) {
	//��ǰ���鳤��
	int len = r - p + 1;
	//�жϳ����Ƿ�С��5��С��5ֱ���������kС����
	if (len <= 5) {
		qsort(num, len, sizeof(int), cmp);
		return num[k - 1];
	}
	else {
		//�������Ϊgroup�飬ÿ��5����
		int group = len / 5;
		int i;
		//������ʣ�������ֵ��m
		int m = len - group * 5;
		//ÿ��group����п�������
		for (i = 0; i < group; i++) {
			qsort(num + i * 5, 5, sizeof(int), cmp);
			//����󣬰�ÿ��group����м�ֵ����mid��
			mid[i] = num[i * 5 + 2];
		}
		//������group����ʣ�࣬��ʣ�������������
		if (m > 0) {
			qsort(num + group * 5, m, sizeof(int), cmp);
			//���м�ֵ��ֵ��mid
			mid[group] = num[group * 5 + m / 2];
			//group+1
			group++;
		}
		//��mid���������ҳ��м�ֵ��ֵ��mm
		qsort(mid, group, sizeof(int), cmp);
		int mm = mid[group / 2];
		//s1�ĳ���Ϊlen_s1,s2�ĳ���Ϊlen_s2
		int len_s1 = 0, len_s2 = 0;
		//��mm(�����������м��ֵ)�������Ϊs1��s2
		for (int i = p-1; i < r; ++i) {
			//��mmС��������s1����mm���������s2
			if (num[i] < mm) {
				s1[len_s1++] = num[i];
			}
			else {
				s2[len_s2++] = num[i];
			}
		}
		int f = 0;
		//���k��ֵ==len_s1+1,˵��mm���ǵ�kС����
		if (k == len_s1 + 1) {
			f = mm;
		}
		else if (k <= len_s1) {
			//���k<=len_s1,˵����kС������s1,�ݹ����select����
			f = select(s1, 1, len_s1, k);
		}
		else {
			//���k>len_s1,˵����kС������s2,�ݹ����select����
			f = select(s2, 1, len_s2, k - len_s1);
		}
		return f;
	}
}
int main() {
	//����ʾ��
	int n[NUM] = { 13,12,11,14,15,7,9,14,16,18,2,4,6,8,10,1,3,5,7,9,2,3};
	printf("%d\n", select(n, 1, 22, 10));
	return 0;
}
