#include <iostream>
#include <string>
#include <fstream>
using namespace std;
constexpr auto N = 100;
void QuickSort(int arr[], int n);

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
	QuickSort(arr, N);
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

// This func is different with another version in quick_sort. 
// In this func, already sort three number
int Median3(int A[], int Left, int Right)
{
    int Center = (Left + Right) / 2;
    if (A[Left] > A[Center])
        Swap(&A[Left], &A[Center]);
    if (A[Left] > A[Right])
	    Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right])
	    Swap(&A[Center], &A[Right]);
    Swap(&A[Center], &A[Right - 1]);
    return  A[Right - 1];
}

void Qsort(int arr[], int l, int r)
{ 
	int mid, Cutoff, Low, High;
	Cutoff = 50;
	if (Cutoff <= r - l) { 
		mid = Median3(arr, l, r);
		Low = l; High = r-1;
		while (1) { 
			while (arr[++Low] < mid);
			while (arr[--High] > mid);
			if (Low < High)
				Swap(&arr[Low], &arr[High]);
			else
				break;
		}
		Swap(&arr[Low], &arr[r - 1]);
		Qsort(arr, l, Low - 1);
		Qsort(arr, Low + 1, r);

	}
    else
		insert_sort(arr + l, r - l + 1);
}
void QuickSort(int arr[], int n){
	     Qsort(arr, 0, n - 1);
}


