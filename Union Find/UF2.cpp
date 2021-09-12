#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int myCount(vector<pair<string, int>>& arr) {	// 返回集合的连通集大小
	int count = 0;
	for (size_t i = 0; i < arr.size(); i++)
		if (arr[i].second < 0)
			++count;
	return count;
}

int myFind(vector<pair<string, int>>& arr, unordered_map<string, int>& hash, string& s) {
	if (arr[hash[s]].second < 0)
		return hash[s];
	return arr[hash[s]].second = myFind(arr, hash, arr[arr[hash[s]].second].first);		// 路径压缩
}

void myUnion(vector<pair<string, int>>& arr, unordered_map<string, int>& hash, string& s1, string& s2) {
	int class1 = myFind(arr, hash, s1);
	int class2 = myFind(arr, hash, s2);
	if (class1 == class2)
		return;
	if (arr[class1].second < arr[class2].second) {	// 按秩归并
		arr[class1].second += arr[class2].second;
		arr[class2].second = class1;
	}
	else {
		arr[class2].second += arr[class1].second;
		arr[class1].second = class2;
	}
		
}


int main() {
	vector<pair<string, int>> arr;		// data和指向父亲的指针（一个整数）
	unordered_map<string, int> hash;	// 将data（这里是string）映射为其下标
	cout << "输入字符串集合，'S'结束：" << endl;
	string input;
	while (1) {
		cin >> input;
		if (input == "S")
			break;
		arr.push_back(make_pair(input, -1));
	}
	for (size_t i = 0; i < arr.size(); i++)
		hash[arr[i].first] = i;
	cout << "I：合并\nC：查询\nN：连通集\nS：结束" << endl;
	char inputI;
	while (1) {
		cin >> inputI;
		string param1, param2;
		if (inputI == 'S')
			break;
		switch (inputI)
		{
		case 'I':
			cin >> param1 >> param2;
			myUnion(arr, hash, param1, param2);
			cout << param1 << "和" << param2 << "连通完毕" << endl;
			break;
		case 'C':
			cin >> param1 >> param2;
			{
				// case里面申请变量需要额外的大括号
				bool res = (myFind(arr, hash, param1) == myFind(arr, hash, param2));
				if (res)
					cout << "YES" << endl;
				else
					cout << "NO" << endl;
			}
			break;
		case 'N':
			cout << "连通集大小为：" << myCount(arr) << endl;;
			break;
		default:break;
		}
	}
	return 0;
}
