#pragma once
#include <iostream>
using namespace std;
#include "MyHeap.h"
#include "MyQueue.h"
#include "UFSet.h"
class EdgeNode {
public:
	int a;
	int b;
	int weight;
	EdgeNode* next;
	bool operator>(const EdgeNode& b) {
		return weight > b.weight;
	}
};

class LGraph {
	

public:
	LGraph(int);
	~LGraph();
	void insert(int, int, int);
	int* kruskal(int);

private:
	int Nv;
	int Ne;
	EdgeNode* g;
};

LGraph::LGraph(int n) {
	Nv = n;
	Ne = 0;
	g = new EdgeNode[n];
	for (int i = 0; i < Nv; i++)
		g[i].next = nullptr;
}

LGraph::~LGraph() {
	EdgeNode* l;
	EdgeNode* r;
	for (int i = 0; i < Nv; i++) {
		l = g[i].next;
		while (l) {
			r = l->next;
			delete l;
			l = r;
		}
	}
	delete[] g;
}

void LGraph::insert(int a, int b, int w) {
	EdgeNode* t = new EdgeNode;
	t->a = a;
	t->b = b;
	t->weight = w;
	t->next = g[a].next;
	g[a].next = t;
	t = new EdgeNode;
	t->a = b;
	t->b = a;
	t->weight = w;
	t->next = g[b].next;
	g[b].next = t;
}

int* LGraph::kruskal(int p) {
	// 初始化
	int* tree = new int[Nv];
	MyHeap<EdgeNode> h;
	UFSet s(Nv);
	EdgeNode* q = new EdgeNode[Nv - 1];	// 存储收集到的边
	for (int i = 0; i < Nv; i++) {
		EdgeNode* t = g[i].next;
		while (t) {
			h.push(*t);
			t = t->next;
		}
		tree[i] = -1;
	}
	EdgeNode cur = h.pop();
	q[0] = cur;
	s.setUnion(cur.a, cur.b);
	int count = 1;

	// 处理
	while (count < Nv - 1 && h.size()>0) {
		cur = h.pop();
		if (s.check(cur.a, cur.b)) {
			;
		}
		else {
			s.setUnion(cur.a, cur.b);
			q[count] = cur;
			++count;
		}	
	}

	// 组成树
	bool* over = new bool[Nv];
	for (int i = 0; i < Nv; i++)
		over[i] = false;
	over[p] = true;
	MyQueue<int> mq;
	mq.push(p);
	int father;
	while (!mq.empty()) {
		father = mq.front();
		mq.pop();
		for (int i = 0; i < Nv - 1; i++) {
			if (q[i].a == father && !over[q[i].b]) {
				if(tree[q[i].b]<0)
					mq.push(q[i].b);
				tree[q[i].b] = father;
				over[q[i].b] = true;
			}
			else if (q[i].b == father && !over[q[i].a]) {
				if (tree[q[i].a]<0)
					mq.push(q[i].a);
				tree[q[i].a] = father;
				over[q[i].a] = true;
			}
		}	
	}
	for (int i = 0; i < Nv; i++)
		cout << tree[i] << " ";
	cout << endl;
	return tree;
}