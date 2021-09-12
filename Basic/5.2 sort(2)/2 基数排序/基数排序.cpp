#include <iostream>
using namespace std;
void show(int a[], int n);
void base_sort(int a[], int n);

int main() {
	int a[] = { 64,8,216,512,27,729,0,1,343,125 };
	int n = sizeof(a) / sizeof(int);
	// ����������Ͱ�����������
	// ����������һ�������Ͱ����
	base_sort_v2(a, n);
	show(a, n);
	return 0;
}

void show(int a[], int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

class node {
public:
	node(int e=0) {
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

int getMaxCircleTimes(int a[], int n) { // ���������������������������������ѭ������
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
	for (int t = 0; t < count; t++) { 
		for (int i = 0; i < n; i++) {	// ��Ͱ�����ݵ�ǰ���������������
			l[(a[i] / base) % 10].insert(a[i]);
		}
		int pos = 0;
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