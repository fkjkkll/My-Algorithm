#include "LGraph.h"
#include <iostream>
using namespace std;

LGraph& init() {
	LGraph* l = new LGraph(7);
	l->insert(0, 1, 2);
	l->insert(0, 2, 4);
	l->insert(0, 3, 1);
	l->insert(1, 3, 3);
	l->insert(1, 4, 10);
	l->insert(2, 3, 2);
	l->insert(3, 4, 7);
	l->insert(2, 5, 5);
	l->insert(3, 5, 8);
	l->insert(3, 6, 4);
	l->insert(4, 6, 6);
	l->insert(5, 6, 1);
	return *l;
}

int main() {
	LGraph& l = init();
	l.kruskal(3);
	return 0;
}



