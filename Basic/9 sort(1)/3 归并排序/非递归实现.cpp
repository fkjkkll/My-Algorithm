#include <iostream>
using namespace std;
void show(int a[], int n);
void merge_sort(int a[], int n);

int main() {
	int a[] = { 11,2,9,5,12,2,1,5,7,10,23,16,3,9,21,11,3 };
	int n = sizeof(a) / sizeof(int);
	merge_sort(a, n);
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

void merge_special(int a[], int t[], int l, int r, int re) {// left , right, right-end
	int le = r - 1;	// left-end
	int pos = l;	// the index of t
	while (l <= le && r <= re) {
		if (a[l] <= a[r])
			t[pos++] = a[l++];
		else
			t[pos++] = a[r++];
	}
	while(l<=le)
		t[pos++] = a[l++];
	while(r<=re)
		t[pos++] = a[r++];

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

void merge_sort(int a[], int n) {
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