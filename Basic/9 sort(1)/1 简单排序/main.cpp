#include <iostream>
using namespace std;
void show(int a[], int n);
void bubble_sort(int a[], int n);
void select_sort(int a[], int n);
void insert_sort(int a[], int n);
int main() {
	int a[] = { 11,2,9,5,12,2,1,5,7,10,23,16,3,9,21,11,3 };
	int n = sizeof(a) / sizeof(int);
	//bubble_sort(a, n);
	//select_sort(a, n);
	insert_sort(a, n);
	show(a, n);
	return 0;
}

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

void show(int a[], int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

void bubble_sort(int a[], int n) {
	for (int i = 0; i < n - 1; i++){
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