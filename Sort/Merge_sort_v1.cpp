#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <fstream>
using namespace std;

const int N = 100;

void sort(int*, int);

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
	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";
	cout << endl;

	sort(arr, N);
	
	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";
	cout << endl;
	
	return 0;
}


void core(int* arr,int* tarr, int l, int r) {
	if (l >= r)
		return;
	int mid = (l + r) / 2;
	core(arr, tarr, l, mid);
	core(arr, tarr, mid + 1, r);
	int pl = l;
	int pr = mid + 1;
	int pt = l;
	while (pl <= mid && pr <= r) {
		if (arr[pl] <= arr[pr]) {
			tarr[pt++] = arr[pl++];
		}
		else {
			tarr[pt++] = arr[pr++];
		}
	}
	while(pl <= mid)
		tarr[pt++] = arr[pl++];
	while(pr <= r)
		tarr[pt++] = arr[pr++];
	for (; l <= r; l++) {
		arr[l] = tarr[l];
	}
}

void sort(int* arr, int n) {
	int* tarr = new int[n];
	core(arr, tarr, 0, n - 1);
	delete[] tarr;
}




 