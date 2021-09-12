#include <iostream>
using namespace std;
void show(int a[], int n);
void merge_recursion_sort(int a[], int n);

int main() {
	int a[] = { 11,2,9,5,12,2,1,5,7,10,23,16,3,9,21,11,3 };
	int n = sizeof(a) / sizeof(int);
	merge_recursion_sort(a, n);
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
	while(i<=m)
		t[pos++] = a[i++];
	while(j<=r)
		t[pos++] = a[j++];
	for (int s = l; s <= r; s++)
		a[s] = t[s];
}

void merge_recursion_sort(int a[], int n) {
	int* t = new int[n];
	merge_recursion(a, t, 0, n - 1);
	delete[] t;
}