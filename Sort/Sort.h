#pragma once
#include <iostream>
using namespace std;
//---------------------------------------------------------------
//							���к���
//---------------------------------------------------------------
void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}
//---------------------------------------------------------------
//							������
//---------------------------------------------------------------
void bubble_sort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
		}
	}
}

void select_sort(int a[], int n) {
	int maxPos;
	int maxValue;
	for (int i = 0; i < n - 1; i++) {
		maxPos = 0;
		maxValue = a[0];
		for (int j = 1; j < n - i; j++) {
			if (a[j] > maxValue) {
				maxPos = j;
				maxValue = a[j];
			}
		}
		swap(a[n - i - 1], a[maxPos]);
	}
}

void insert_sort(int a[], int n) {
	int i, j, tmp;
	for (i = 1; i < n; i++) {
		tmp = a[i];
		for (j = i; j > 0 && a[j - 1] > tmp; j--) {
			a[j] = a[j - 1];
		}
		a[j] = tmp;
	}
}
//---------------------------------------------------------------
//							������
//---------------------------------------------------------------
void percDown(int a[], int i, int n) {
	int tmp = a[i];
	int father = i;
	int child = father * 2 + 1;
	for (; child < n;) {
		if (child + 1 < n && a[child] < a[child + 1])
			++child;
		if (tmp > a[child])
			break;
		else {
			a[father] = a[child];
			father = child;
			child = father * 2 + 1;
		}
	}
	a[father] = tmp;
}

void heap_sort(int a[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		percDown(a, i, n);
	}
	for (int i = n - 1; i > 0; i--) {
		swap(a[0], a[i]);
		percDown(a, 0, i);
	}
}
//---------------------------------------------------------------
//							�鲢����-�ݹ�
//---------------------------------------------------------------
void merge_recursion(int a[], int t[], int l, int r) {
	if (l >= r)
		return;
	int m = (l + r) / 2;
	merge_recursion(a, t, l, m);
	merge_recursion(a, t, m + 1, r);
	int i = l;
	int j = m + 1;
	int pos = l;
	while (i <= m && j <= r) {
		if (a[i] <= a[j])
			t[pos++] = a[i++];
		else
			t[pos++] = a[j++];
	}
	while (i <= m)
		t[pos++] = a[i++];
	while (j <= r)
		t[pos++] = a[j++];
	for (int s = l; s <= r; s++)
		a[s] = t[s];
}

void merge_sort_recursion(int a[], int n) {
	int* t = new int[n];
	merge_recursion(a, t, 0, n - 1);
	delete[] t;
}
//---------------------------------------------------------------
//							�鲢����-�ǵݹ�
//---------------------------------------------------------------
void merge_special(int a[], int t[], int l, int r, int re) {// left , right, right-end
	int le = r - 1;	// left-end
	int pos = l;	// the index of t
	while (l <= le && r <= re) {
		if (a[l] <= a[r])
			t[pos++] = a[l++];
		else
			t[pos++] = a[r++];
	}
	while (l <= le)
		t[pos++] = a[l++];
	while (r <= re)
		t[pos++] = a[r++];
	// ����Ҫд�أ���֮ǰmerge��ͬ
}

void merge_pass(int a[], int t[], int n, int length) {
	int i = 0;
	for (; i < n - 2 * length; i += 2 * length) {
		merge_special(a, t, i, i + length, i + 2 * length - 1);
	}
	if (i + length < n)	// leftover: "special processing"
		merge_special(a, t, i, i + length, n - 1);
	else
		for (int j = i; j < n; j++)
			t[j] = a[j];
}

void merge_sort_std(int a[], int n) {
	int* t = new int[n];
	int length = 1;	// "merge radius"
	while (length < n) {
		merge_pass(a, t, n, length);
		length *= 2;
		merge_pass(t, a, n, length);
		length *= 2;
	}
	delete[] t;
}
//---------------------------------------------------------------
//							��������-���԰�
//---------------------------------------------------------------
void quickSort_simple(int a[], int l, int r) {
	static int cutOff = 1;
	if (r - l > cutOff) {
		int tmp = a[l];
		int i = l;
		int j = r + 1;
		while (1) {
			while (a[--j] > tmp);
			if (i < j)
				a[i] = a[j];
			else
				break;
			while (a[++i] < tmp);
			if (i < j)
				a[j] = a[i];
			else
				break;
		}
		a[i] = tmp;
		quickSort_simple(a, l, i - 1);
		quickSort_simple(a, i + 1, r);
	}
	else
		insert_sort(a + l, r - l + 1);
}

void quick_sort_simple(int a[], int n) {
	quickSort_simple(a, 0, n - 1);
}
//---------------------------------------------------------------
//							��������-��׼��
//---------------------------------------------------------------
int median3(int a[], int l, int r) {
	int m = (l + r) / 2;
	if (a[l] > a[m])
		swap(a[l], a[m]);
	if (a[l] > a[r])
		swap(a[l], a[r]);
	if (a[m] > a[r])
		swap(a[m], a[r]);
	swap(a[m], a[r - 1]);
	return a[r - 1];
}

void quickSort_std(int a[], int l, int r) {
	static int cutOff = 100;
	if (r - l > cutOff) {
		int tmp = median3(a, l, r);
		int i = l;
		int j = r - 1;
		while (1) {
			while (a[++i] < tmp);
			while (a[--j] > tmp);
			if (i < j)
				swap(a[i], a[j]);
			else
				break;
		}
		swap(a[i], a[r - 1]);
		quickSort_std(a, l, i - 1);
		quickSort_std(a, i + 1, r);
	}
	else
		insert_sort(a + l, r - l + 1);
}

void quick_sort_std(int a[], int n) {
	quickSort_std(a, 0, n - 1);
}
//---------------------------------------------------------------
//							��������v1��v2
//---------------------------------------------------------------
class node {
public:
	node(int e = 0) {
		num = e;
		next = nullptr;
	}
	int num;
	node* next;
};

class link {
public:
	link() {
		head = tail = new node;
	}
	void insert(int e) {
		node* tmp = new node(e);
		tail->next = tmp;
		tail = tmp;
	}
	void clear() {
		node* l = head->next;
		node* r;
		while (l) {
			r = l->next;
			delete l;
			l = r;
		}
		tail = head;
		tail->next = nullptr;
	}
	node* head;
	node* tail;
};

int getMaxCircleTimes(int a[], int n) {	// ���������������������������������ѭ������
	int max = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] > max)
			max = a[i];
	}
	int count = 0;
	while (max) {
		++count;
		max /= 10;
	}
	return count;
}

void base_sort_v1(int a[], int n) {
	link l[10];
	int base = 1;
	int count = getMaxCircleTimes(a, n);
	int pos;
	for (int t = 0; t < count; t++) {
		for (int i = 0; i < n; i++) {	// ��Ͱ�����ݵ�ǰ���������������
			l[(a[i] / base) % 10].insert(a[i]);
		}
		pos = 0;
		for (int b = 0; b < 10; b++) {	// �ռ����������ڵ����Ż�������
			node* tmp = l[b].head->next;
			while (tmp) {
				a[pos++] = tmp->num;
				tmp = tmp->next;
			}
			l[b].clear();
		}
		base *= 10;
	}
}

void base_sort_v2(int a[], int n) {
	link l[10];
	node* list = nullptr;
	int base = 1;
	int count = getMaxCircleTimes(a, n);
	node* tmp;
	node* nxt;
	for (int i = 0; i < n; i++) {	// ������ȫ������list��
		tmp = new node(a[i]);
		tmp->next = list;
		list = tmp;
	}
	int b;
	for (int t = 0; t < count; t++) {
		tmp = list;
		while (tmp) {	// ��Ͱ�����ݴ�list����Ͱ��
			nxt = tmp->next;
			b = (tmp->num / base) % 10;
			tmp->next = nullptr;
			l[b].tail->next = tmp;
			l[b].tail = tmp;
			tmp = nxt;
		}
		list = nullptr;
		for (int b = 9; b >= 0; b--) {	// �ռ����������ڵ����Ż�list
			if (l[b].head->next) {
				l[b].tail->next = list;
				list = l[b].head->next;
				l[b].head->next = nullptr;
				l[b].tail = l[b].head;
			}
		}
		base *= 10;
	}
	for (int i = 0; i < n; i++) {	// list�Ż�ԭ����
		tmp = list;
		list = list->next;
		a[i] = tmp->num;
		delete tmp;
	}
}