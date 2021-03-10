#include <iostream>

using namespace std;


int bag(int weight[], int value[], int n, int w) {
	int pick, notpick;

	int *dp = new int[w + 1];
	dp[0] = 0;
	for (int i = 1; i < w + 1; i++) {
		dp[i] = weight[0] > i ? 0 : value[0];
	}

	for (int row = 1; row < n; row++) {
		for (int col = w; col > 0; col--) {

			if (weight[row] <= col) {
				pick = value[row] + dp[col - weight[row]];
				notpick = dp[col];
				dp[col] = pick > notpick ? pick : notpick;
			}
		}
	}

	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < w+1; j++)
	//	{
	//		cout << dp[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	return dp[w];
}


int main() {
	int w, n;
	cin >> w >> n;
	int *weight = new int[n];
	int *value = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> weight[i] >> value[i];
	}
	int result = bag(weight, value, n, w);
	cout << result;
	return 0;
}