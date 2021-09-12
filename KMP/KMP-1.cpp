#include <iostream>
using namespace std;

bool getNext(char p[], int next[], int n) {
	for (int i = 0; i < n; i++)
		next[i] = 0;
	int i = 1, j = 0;
	while (i < n) {
		if (p[i] == p[j])
			next[i++] = ++j;
		else
			if (j > 0)
				j = next[j - 1];
			else
				++i;
	}
	return true;
}

int KMP(char s[], int ns, char p[], int np) {
	int* next = new int[np];
	getNext(p, next, np);
	int i = 0, j = 0;
	while (i < ns) {
		if (s[i] == p[j]) {
			++i;
			++j;
			if (j == np)
				return i - j;
		}
		else
			if (j > 0)
				j = next[j - 1];
			else
				++i;
	}
	return -1;
}

int main() {
	char s[] = "asdwdaaaaaaaabaasd";
	char p[] = "aaaaab";
	int ns = sizeof(s) / sizeof(char) - 1;
	int np = sizeof(p) / sizeof(char) - 1;
	cout << KMP(s, ns, p, np) << endl;
	return 0;
}