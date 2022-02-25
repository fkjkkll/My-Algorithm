// 并查集类（需要将集合元素映射为整数）
class UF {
public:
	UF(int _n) :count(_n), parent(_n, -1) {}
	int getCount() { return count; }
	bool isConnected(int a, int b) {
		int class1 = find(a);
		int class2 = find(b);
		return class1 == class2;
	}
	void toUnion(int a, int b) {
		int class1 = find(a);
		int class2 = find(b);
		if (class1 == class2)
			return;
		if (parent[class1] < parent[class2]) {
			parent[class1] += parent[class2];
			parent[class2] = class1;
		}
		else {
			parent[class2] += parent[class1];
			parent[class1] = class2;
		}
		--count;
	}

private:
	int find(int pos) {
		if (parent[pos] < 0)
			return pos;
		return parent[pos] = find(parent[pos]);
	}

	int count;
	vector<int> parent;
};

// leetcode 990
class Solution {
public:
	bool equationsPossible(vector<string>& equations) {
		UF a(26);
		for (int i = 0; i < equations.size(); i++) {
			if (equations[i][1] == '=') {
				a.toUnion(equations[i][0] - 97, equations[i][3] - 97);
			}
		}
		for (int i = 0; i < equations.size(); i++) {
			if (equations[i][1] == '!') {
				if (a.isConnected(equations[i][0] - 97, equations[i][3] - 97))
					return false;
			}
		}
		return true;
	}
};
