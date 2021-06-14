#include <iostream>
#include <fstream>
#include <time.h>
#include "Sort.h"
constexpr auto N = 10000;
using namespace std;
void show(int a[], int n);

int main() {
	//-------------------- read file ---------------------//
	fstream file;
	file.open("Data.txt", ios::in);
	if (!file) {
		cout << "file not founded!" << endl;
	}
	int* a = new int[N];
	int pos = 0;
	while (!file.eof() && pos < N) {
		file >> a[pos++];
	}
	file.close();
	//------------------- read file end ------------------//
	clock_t start, stop;
	double duration;
	start = clock();

	//bubble_sort(a, N);
	//select_sort(a, N);
	//insert_sort(a, N);
	//heap_sort(a, N);
	//merge_sort_recursion(a, N);
	//merge_sort_std(a, N);
	//quick_sort_simple(a, N);
	//quick_sort_std(a, N);
	//base_sort_v1(a, N);
	//base_sort_v2(a, N);

	stop = clock();
	duration = (((double)stop - start)) / CLK_TCK;
	printf("ticks = %f\n", (double)stop - start);

	//show(a, N);
	return 0;
}

void show(int a[], int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

