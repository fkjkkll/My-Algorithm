#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
	int knapsack(vector<int>& weight, vector<int>& value, int maxW) {
		// 物品数目
		int kinds = weight.size();
		// dp数组初始化为二维数组
		vector<vector<int>> dp(kinds + 1, vector<int>(maxW + 1, 0));
		// 状态一：可选的目标：0个可选，前一个可选、前两个可选、前三个可选，以此类推（与找零钱不同，物品不能重复选）
		for (int c = 1; c <= kinds; c++) {
			// 状态二：当前的可承载重量，0、1、2...maxW
			for (int w = 1; w <= maxW; w++) {
				// 该物品太大以至于当前重量超标：下标越界，直接赋值为“没有该物品时的最优答案”
				if (w - weight[c - 1] < 0) 
					dp[c][w] = dp[c - 1][w];
				// 比较，“不选择该物品”和“选择该物品”时，哪个价值大
				else
					dp[c][w] = max(dp[c - 1][w], dp[c - 1][w - weight[c - 1]] + value[c - 1]);
			}
		}

		// 显示dp数组
		for (int i = 0; i <= kinds; i++) {
			for (int j = 0; j <= maxW; j++) {
				cout << dp[i][j] << "\t";
			}
			cout << endl;
		}
		return dp[kinds][maxW];
	}
};

int main() {
	vector<int> weight = { 2, 1, 3, 3 };
	vector<int> value = { 12, 10, 20, 15 };
	int maxW = 5;
	int r = Solution().knapsack(weight, value, maxW);
	cout << "ans: " << r << endl;
	return 0;
}






