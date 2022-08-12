#include <iostream>
using namespace std;
void show(int a[], int n);
void heap_sort(int a[], int n);

int main() {
	int a[] = { 11,2,9,5,12,2,1,5,7,10,23,16,3,9,21,11,3 };
	int n = sizeof(a) / sizeof(int);
	heap_sort(a, n);
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

void percDown(int a[], int i, int n) {
	int tmp = a[i];
	int father = i;
	int child = father * 2 + 1;
	for (;child<n;) {
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