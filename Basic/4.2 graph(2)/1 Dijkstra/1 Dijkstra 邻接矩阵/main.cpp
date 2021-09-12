#include <iostream>
#include "MyStack.h"
#include "MyQueue.h"
#include "MyHeap.h"
#include "MyStack.h"
#include "Graph.h"
using namespace std;

int main() {
	// 初始化图
	int Nv, Ne;
	cout << "输入顶点数和边数：";
	cin >> Nv >> Ne;
	Graph<int, char> g(Nv);
	char m;
	cout << "输入"<<Nv<<"个顶点的标记：";
	for (int i = 0; i < Nv; i++) {
		cin >> m;
		g.setMark(i, m);
	}
	Vertex a, b;
	int w;
	for (int i = 0; i < Ne; i++) {
		cout << "输入第" << i+1 << "个边的起点、终点、权值：";
		cin >> a >> b >> w;
		g.insertEdge(Edge<int>(a-1, b-1, w));
	}

	// 寻找路径
	cout << "输入出发点和目的地序号：";
	cin >> a >> b;
	Vertex* path = g.findPath(a - 1);

	// 结果显示
	MyStack<Vertex> s;
	--b;
	while (b>=0) {
		s.push(b);
		b = path[b];
	}
	while (!s.empty()) {
		cout << s.top() + 1 << " ";
		s.pop();
	}
	cout << endl;
	return 0;
}

