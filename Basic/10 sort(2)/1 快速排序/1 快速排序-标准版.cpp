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

void quickSort(int a[], int l, int r) {
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
		quickSort(a, l, i - 1);
		quickSort(a, i + 1, r);
	}
	else
		insert_sort(a + l, r - l + 1);
}

void quick_sort(int a[], int n) {
	quickSort(a, 0, n - 1);
}

