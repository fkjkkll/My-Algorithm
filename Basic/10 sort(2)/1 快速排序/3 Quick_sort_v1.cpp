#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

int* readfile(int);
void show(int* arr, int, int);
void quick_sort(int*, int);
void insert_sort(int* arr, int n);
int main() {
	double duration;
	clock_t start, finish;
	const int size = 200000;
	int* arr = readfile(size);

	//----------test----------
	start = clock();
	quick_sort(arr, size);
	//insert_sort(arr, size);
	finish = clock();
	//----------test----------

	duration = ((double)finish - start) / CLOCKS_PER_SEC;
	cout << "time:" << 1000 * duration << "ms" << endl;
	//show(arr, 0, size-1);
	return 0;
}

int* readfile(int n) {
	fstream file;
	file.open("data.txt", ios::in);
	if (!file) {
		cout << "file not founded!" << endl;
	}
	int* arr = new int[n];
	int pos = 0;
	while (!file.eof() && pos < n) {
		file >> arr[pos++];
	}
	file.close();
	return arr;
}

void show(int* arr, int l, int r) {
	for (int i = l; i < r; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void Swap(int* a, int* b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void insert_sort(int* arr, int n) {
	int temp, i, j;
	for (i = 1; i < n; i++) {
		temp = arr[i];
		for (j = i - 1; j >= 0 && arr[j]>temp; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
	}
}


void quick_sort_inner(int* arr, int l, int r) {
	if (r - l < 100) {
		insert_sort(arr + l, r - l + 1);
		return;
	}
		
	int temp = arr[l];
	int old_l = l;
	int old_r = r++;
	while (1) {
		while (arr[--r] > temp);
		if (r > l)
			arr[l] = arr[r];
		else
			break;
		while (arr[++l] < temp);
		if (r > l)
			arr[r] = arr[l];
		else
			break;
	}
	arr[l] = temp;
	quick_sort_inner(arr, old_l, l - 1);
	quick_sort_inner(arr, l+1, old_r);
}

void quick_sort(int* arr, int n) {
	quick_sort_inner(arr, 0, n - 1);
}



