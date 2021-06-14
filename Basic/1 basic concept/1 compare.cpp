#include<stdio.h>
#include<time.h>
#include<math.h>
#define MAXN 10
double f1(int n, double a[], double x) {
	double p = a[0];
	for (int i = 1; i <= n; i++) {
		p += (a[i] * pow(x, i));
	}
	return p;
}

double f2(int n, double a[], double x) {
	double p = a[n];
	for (int i = n; i > 0; i--) {
		p = a[i - 1] + x * p;
	}
	return p;
}

int main() {
	double a[MAXN];
	for (int i = 0; i < MAXN; i++)
		a[i] = (double)i;
	clock_t start, stop;
	double duration;
	start = clock();
	for (int i = 0; i < 100000; i++)
		f2(MAXN, a, 1.1);// 居然快了接近一个数量级
	stop = clock();
	duration = (((double)stop - start)) / CLK_TCK;
	printf("ticks = %f\n", (double)stop - start);
	printf("duration = %6.2e\n", duration);
	return 0;
}

