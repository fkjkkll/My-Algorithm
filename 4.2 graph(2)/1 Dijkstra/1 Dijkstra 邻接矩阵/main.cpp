#include <iostream>
#include "MyStack.h"
#include "MyQueue.h"
#include "MyHeap.h"
#include "MyStack.h"
#include "Graph.h"
using namespace std;

int main() {
	// ��ʼ��ͼ
	int Nv, Ne;
	cout << "���붥�����ͱ�����";
	cin >> Nv >> Ne;
	Graph<int, char> g(Nv);
	char m;
	cout << "����"<<Nv<<"������ı�ǣ�";
	for (int i = 0; i < Nv; i++) {
		cin >> m;
		g.setMark(i, m);
	}
	Vertex a, b;
	int w;
	for (int i = 0; i < Ne; i++) {
		cout << "�����" << i+1 << "���ߵ���㡢�յ㡢Ȩֵ��";
		cin >> a >> b >> w;
		g.insertEdge(Edge<int>(a-1, b-1, w));
	}

	// Ѱ��·��
	cout << "����������Ŀ�ĵ���ţ�";
	cin >> a >> b;
	Vertex* path = g.findPath(a - 1);

	// �����ʾ
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

