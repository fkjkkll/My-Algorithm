#include<stdio.h>
#include<time.h>
#include<math.h>
#define TESTTIME 10000

void test();
int algorithm_1(int a[], int n);
int algorithm_2(int a[], int n);
int algorithm_3(int a[], int n);
int algorithm_4(int a[], int n);

int main() {
	clock_t start, stop;
	double duration;
	start = clock();
	for (int i = 0; i < TESTTIME; ++i) {
		test();
	}
	stop = clock();
	duration = (((double)stop - start)) / CLK_TCK;
	printf("ticks = %f\n", (double)stop - start);
	printf("duration = %6.2es\n", duration);
	return 0;
}

void test() {
	int a[] = { 4,-3,5,-2,-1,2,6,-2,-5,1,-2,3,-1,5,0,2,3,4,-5,-3,3,4,-5,3,0,7,-6,3,2,5,-1,-7,6,-9,1,5,1,-2,-7,8,4,-3,5,-2,-1,2,6,-2,-5,1,-2,3,-1,5,0,2,3,4,-5,-3,3,4,-5,3,0,7,-6,3,2,5,-1,-7,6,-9,1,5,1,-2,-7,8 };
	int ans = algorithm_4(a, sizeof(a)/sizeof(int));
	//printf("ans=%d\n", ans);
}

int algorithm_1(int a[], int n) {	// N^3
	int Max = 0;
	int temp;
	for (int i = 0; i < n; ++i){
		for (int j = i; j < n; ++j) {
			temp = 0;
			for (int k = i; k <= j; ++k)
				temp += a[k];
			if (temp > Max)
				Max = temp;
		}
	}
	return Max;
}

int algorithm_2(int a[], int n) {	// N^2
	int Max = 0;
	int temp;
	for (int i = 0; i < n; ++i) {
		temp = 0;
		for (int j = i; j < n; ++j) {
			temp += a[j];
			if (temp > Max)
				Max = temp;
		}
	}
	return Max;
}

int algorithm_3_recursion(int a[], int l, int r) {
	if (l == r)
		return a[l] > 0 ? a[l] : 0;
	int mid = (l + r) / 2;
	int lMax = algorithm_3_recursion(a, l, mid);
	int rMax = algorithm_3_recursion(a, mid+1, r);
	int mlMax = 0;
	int mrMax = 0;
	int temp = 0;
	for (int i = mid; i >= l; --i) {
		temp += a[i];
		if (temp > mlMax)
			mlMax = temp;
	}
	temp = 0;
	for (int i = mid+1; i <= r; ++i) {
		temp += a[i];
		if (temp > mrMax)
			mrMax = temp;
	}
	int mMax = mlMax + mrMax;
	return lMax > rMax ? (lMax > mMax ? lMax : mMax) : (rMax > mMax ? rMax : mMax);
}

int algorithm_3(int a[], int n) {	// NlogN
	return algorithm_3_recursion(a, 0, n-1);
}

int algorithm_4(int a[], int n) {	// N
	int Max = 0;
	int temp = 0;
	for (int i = 0; i < n; i++) {
		temp += a[i];
		if (temp > Max)
			Max = temp;
		if (temp < 0)
			temp = 0;
	}
	return Max;
}
