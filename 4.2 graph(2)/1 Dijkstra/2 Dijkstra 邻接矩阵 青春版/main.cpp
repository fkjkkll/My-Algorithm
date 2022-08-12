#include <iostream>
#include "MyHeap.h"
using namespace std;
constexpr auto M = 1024;
constexpr auto N = 9;

int map[N][N] = {
	{0,4,M,M,M,M,M,8,M},
	{4,0,8,M,M,M,M,3,M},
	{M,8,0,7,M,4,M,M,2},
	{M,M,7,0,9,14,M,M,M},
	{M,M,M,9,0,10,M,M,M},
	{M,M,4,14,10,0,2,M,M},
	{M,M,M,M,M,2,0,6,6},
	{8,3,M,M,M,M,6,0,1},
	{M,M,2,M,M,M,6,1,0}
};
int dist[N];
int path[N];
bool s[N];

int findMin() {
	int pos = -1, minValue = M;
	for (int i = 0; i < N; i++) {
		if (!s[i] && dist[i] < minValue) {
			minValue = dist[i];
			pos = i;
		}
	}
	return pos;
}

void dijkstra(int a) {
	// 初始化伴随数组
	for (int i = 0; i < N; i++) {
		dist[i] = map[a][i];
		s[i] = false;
		path[i] = map[a][i] < M ? a : -1;
	}
	s[a] = true;
	// 开始处理
	while (1) {
		int cur = findMin();
		if (cur < 0)
			break;
		s[cur] = true;
		for (int w = 0; w < N; w++) {
			if (!s[w] && map[cur][w]<M && dist[w]>dist[cur] + map[cur][w]) {
				dist[w] = dist[cur] + map[cur][w];
				path[w] = cur;
			}
		}
	}
}

void showRoad(int a, int b) {
	if (a == b){
		cout << a <<" ";
		return;
	}
	showRoad(a, path[b]);
	cout << b << " ";
}

int main() {
	int start = 0;
	int end = 4;
	dijkstra(start);
	showRoad(start, end);
	return 0;
}



