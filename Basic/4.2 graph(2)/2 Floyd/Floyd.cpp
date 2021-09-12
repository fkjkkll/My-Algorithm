#include <iostream>
using namespace std;
constexpr auto M = 1024;
constexpr auto N = 5;
int map[N][N] = {
	{0,3,8,M,-4},
	{M,0,M,1,7},
	{M,4,0,M,M},
	{2,M,-5,0,M},
	{M,M,M,6,0}
};
int dist[N][N];
int path[N][N];

void floyd() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist[i][j] = map[i][j];
			path[i][j] = j;
		}
	}
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;
				}
			}
		}
	}
}

void showRoad(int a, int b) {
	if (path[a][b] == b) {
		cout << a << "->" << b << endl;
		return;
	}
	int k = path[a][b];
	showRoad(a, k);
	showRoad(k, b);
}

int main() {
	floyd();
	showRoad(3, 4);
	return 0;
}



