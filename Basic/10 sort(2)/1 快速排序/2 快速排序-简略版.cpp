#include <iostream>
using namespace std;
void show(int a[], int n);
void quick_sort(int a[], int n);

int main() {
	int a[] = { 11,2,9,5,12,2,1,5,7,10,23,16,3,9,21,11,3 };
	int n = sizeof(a) / sizeof(int);
	quick_sort(a, n);
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

void quickSort(int a[], int l, int r) {
	static int cutOff = 100;
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
		quickSort(a, l, i - 1);
		quickSort(a, i + 1, r);
	}
	else
		insert_sort(a + l, r - l + 1);
}

void quick_sort(int a[], int n) {
	quickSort(a, 0, n - 1);
}

