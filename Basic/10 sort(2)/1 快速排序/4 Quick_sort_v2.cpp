#include <iostream>
#include <string>
#include <fstream>
using namespace std;
constexpr auto N = 100;

void quick_sort(int[], int);

int main() {
	//-------------------- read file ---------------------//
	fstream file;
	file.open("d.txt", ios::in);
	if (!file) {
		cout << "file not founded!" << endl;
	}
	int arr[N];
	int pos = 0;
	while (!file.eof() && pos < N) {
		file >> arr[pos++];
	}
	file.close();
	//------------------- read file end ------------------//
	quick_sort(arr, N);
	return 0;
}

void Swap(int *a, int *b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void insert_sort(int arr[], int n) {
	int cur, i, k;
	for (i = 1; i < n; i++) {
		cur = arr[i];
		for (k = i - 1; k >= 0 && arr[k] > cur; k--) {
			arr[k + 1] = arr[k];
		}
		arr[++k] = cur;
	}
}

int quick_sort_pre(int arr[], int l, int r) {
	int t, mid, c;
	mid = (l + r) / 2;
	c = arr[l] > arr[r] ? (arr[mid] > arr[l] ? (l) : (arr[mid] > arr[r] ? mid : r)) : (arr[mid] > arr[r] ? (r) : (arr[mid] > arr[l] ? mid : l));
	t = arr[c];
	arr[c] = arr[r];
	arr[r] = t;
	return t;
}

void quick_sort_recur(int arr[], int l, int r) {
	int mid, origi_l, origi_r;
	origi_l = l;
	origi_r = r;
	if (r - l < 50)
		insert_sort(arr + l, r - l + 1);
	else {
		mid = quick_sort_pre(arr, l, r--);
		while (1) {
			while (arr[l] < mid)
				++l;
			while (arr[r] > mid)
				--r;
			if (l < r)
				Swap(&arr[l++], &arr[r--]);		
			else
				break;
		}
		Swap(&arr[l], &arr[origi_r]);
		quick_sort_recur(arr, origi_l, l-1);
		quick_sort_recur(arr, l+1, origi_r);
	}
}

void quick_sort(int arr[], int n) {
	quick_sort_recur(arr, 0, n - 1);
}



