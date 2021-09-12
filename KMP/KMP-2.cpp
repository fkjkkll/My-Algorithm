#include <iostream>
using namespace std;

bool getNext(char p[], int next[], int n) {
	next[0] = -1;
	int i = 0, j = -1;
	while (i < n) {
		if (j == -1 || p[i] == p[j])
			next[++i] = ++j;
		else
			j = next[j];
	}
	return true;
}

int KMP(char s[], int ns, char p[], int np) {
	int* next = new int[np];
	getNext(p, next, np);
	int i = 0, j = 0;
	while (i < ns) {
		if (j==-1 || s[i] == p[j]) {
			++i;
			++j;
			if (j == np)
				return i - j;
		}
		else
			j = next[j];
	}
	return -1;
}

int main() {
	char s[] = "ddaasdsaasdwdaaaabababcaaaaaabaasdasdsad";
	char p[] = "dasdsa";
	int ns = sizeof(s) / sizeof(char) - 1;
	int np = sizeof(p) / sizeof(char) - 1;
	cout << KMP(s, ns, p, np) << endl;
	return 0;
}