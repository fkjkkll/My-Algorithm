#pragma once

class UFSet {
public:
	UFSet(int);
	bool check(int, int);
	void setUnion(int, int);

private:
	int find(int);

private:
	int* data;
};

UFSet::UFSet(int n) {
	data = new int[n];
	for (int i = 0; i < n; i++)
		data[i] = -1;
}

int UFSet::find(int e) {
	if (data[e] < 0)
		return e;
	else
		return data[e] = find(data[e]);
}

bool UFSet::check(int a, int b) {
	int root1 = find(a);
	int root2 = find(b);
	return root1 == root2;
}

void UFSet::setUnion(int a, int b) {
	int root1 = find(a);
	int root2 = find(b);
	if (data[root2] < data[root1])
		data[root1] = root2;
	else {
		if (data[root1] == data[root2])
			-- data[root1];
		data[root2] = root1;
	}
}