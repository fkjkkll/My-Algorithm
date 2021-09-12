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
int parent[N];

int findMin() {
	int pos = -1, minValue = M;
	for (int i = 0; i < N; i++) {
		if (dist[i] && dist[i] < minValue) {
			minValue = dist[i];
			pos = i;
		}
	}
	return pos;
}

void prim(int r) { // 需指定一个起点
	// 初始化伴随数组
	for (int i = 0; i < N; i++){
		dist[i] = map[r][i];
		parent[i] = map[r][i] < M ? r : -1;
	}
	parent[r] = -1;

	// 处理
	while (1) {
		int c = findMin();
		if (c < 0)
			break;
		dist[c] = 0;
		for (int w = 0; w < N; w++) {
			if (dist[w] && dist[w] > map[c][w]) {
				dist[w] = map[c][w];
				parent[w] = c;
			}
		}
	}

	// 判断是否得到正确结果
	int count = 0;
	for (int i = 0; i < N; i++)
		if (parent[i] == -1)
			++count;
	if (count > 1)
		cout << "图不连通！" << endl;

	// 显示path
	for (int i = 0; i < N; i++)
		cout << parent[i] << " ";
	cout << endl;
}

int main() {
	prim(0);
	return 0;
}



