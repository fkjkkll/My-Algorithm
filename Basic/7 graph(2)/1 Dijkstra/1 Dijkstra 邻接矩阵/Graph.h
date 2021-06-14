#pragma once
#include "MyHeap.h"
constexpr auto MAXDIS = 1024;
typedef int Vertex;

template <class T>
class Edge {
public:
	Edge(Vertex a, Vertex b, T c) {
		v1 = a;
		v2 = b;
		weight = c;
	}
	Vertex v1;
	Vertex v2;
	T weight;
};

template <class T1, class T2>
class Graph {
public:
	Graph(int);
	void insertEdge(const Edge<T1>&);
	void setMark(Vertex, const T2&);
	Vertex* findPath(Vertex);

private:
	int Nv;
	int Ne;
	T1** G;
	T2* Data;
};

template <class T1, class T2>
Graph<T1, T2>::Graph(int n) {
	Nv = n;
	Ne = 0;
	G = new T1*[n];
	for (int i = 0; i < n; i++) {
		G[i] = new T1[n];
		for (int j = 0; j < n; j++) {
			G[i][j] = 0;
		}
	}
	Data = new T2[n];
}

template <class T1, class T2>
void Graph<T1, T2>::insertEdge(const Edge<T1>& e) {
	G[e.v1][e.v2] = e.weight;
	++ Ne;
}

template <class T1, class T2>
void Graph<T1, T2>::setMark(Vertex v, const T2& m) {
	Data[v] = m;
}

template <class T1, class T2>
Vertex* Graph<T1, T2>::findPath(Vertex a) {
	// 初始化dist collected path 数组
	class distNode{
	public:
		int value;
		Vertex v;
		distNode() {
			value = 0;
			v = -1;
		}
		bool operator>(const distNode& another) {
			return this->value > another.value;
		}
	};
	distNode* dist = new distNode[Nv];
	bool* collected = new bool[Nv];
	Vertex* path = new Vertex[Nv];
	for (int i = 0; i < Nv; i++) {
		collected[i] = false;
		path[i] = -1;
		dist[i].v = i;
		if (G[a][i]) {
			dist[i].value = G[a][i];
			path[i] = a;
		}
		else
			dist[i].value = MAXDIS;
	}
	dist[a].value = 0;
	collected[a] = true;
	MyHeap<distNode> h(dist, Nv);
	h.pop();
	// 开始处理
	while (1) {
		distNode d = h.pop();
		if (collected[d.v]) {
			break;
		}
		collected[d.v] = true;
		for (int w = 0; w < Nv; w++) {
			if ( G[d.v][w] && !collected[w]) {
				if (dist[w].value > dist[d.v].value + G[d.v][w]) {
					dist[w].value = dist[d.v].value + G[d.v][w];
					h.push(dist[w]);	// 最小堆的更新是通过插入来完成的，之前旧的不去管理
					path[w] = d.v;
				}
			}
		}
	}
	return path;
}